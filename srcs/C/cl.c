/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/21 02:25:45 by agrumbac          #+#    #+#             */
/*   Updated: 2017/06/21 17:35:47 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		cl_init(t_cl *cl)
{
	cl_platform_id		platform_id = NULL;
	cl_device_id 		device_id = NULL;
	cl_uint				ret_num_devices;
	cl_uint				ret_num_platforms;
	cl_int				ret;
	int					fd;
	ssize_t 			source_size;
	char				source_str[MAX_SOURCE_SIZE];
	const char			*source_str_ptr = source_str;

	if ((fd = open(CL_FILENAME, O_RDONLY)) == -1)
		errors(0, 0);
	if ((source_size = read(fd, &source_str, MAX_SOURCE_SIZE)) == -1)
		errors(0, 0);
	close(fd);
	if (clGetPlatformIDs(1, &platform_id, &ret_num_platforms) || \
		clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_DEFAULT, 1, &device_id, \
		&ret_num_devices))
		errors(1, "cl*ID failure --");
	cl->context = clCreateContext(NULL, 1, &device_id, NULL, NULL, &ret);
	ret ? errors(1, "clCreateContext failure --") : 0;
	cl->command_queue = clCreateCommandQueue(cl->context, device_id, 0, &ret);
	ret ? errors(1, "clCreateCommandQueue failure --") : 0;
	cl->program = clCreateProgramWithSource(cl->context, 1, \
		(const char **)&source_str_ptr, (const size_t *)&source_size, &ret);
	ret ? errors(1, "clCreateProgramWithSource failure --") : 0;
	if (clBuildProgram(cl->program, 1, &device_id, NULL, NULL, NULL))
		errors(1, "clBuildProgram failure --");
	cl->work_size = WIN_H * WIN_W;
}

void		cl_start(t_cl *cl, const char *kernel_name, const int nb_args, ...)
{
	cl_int		ret;
	t_arg		arg;
	va_list		ap;
	int			i;

	if (!nb_args || nb_args > MAX_KERNEL_ARGS)
		errors(1, "cl_start: bad nb_args --");
	va_start(ap, nb_args);

	i = 0;
	while (i < nb_args)
	{
		arg = va_arg(ap, t_arg);

		cl->memobj[i] = clCreateBuffer(cl->context, CL_MEM_READ_WRITE, arg.size, NULL, &ret);
		ret ? errors(1, "clCreateBuffer failure --") : 0;
		/* Create OpenCL Kernel */
		cl->kernel = clCreateKernel(cl->program, kernel_name, &ret);
		ret ? errors(1, "clCreateKernel failure --") : 0;
		/* Set OpenCL Kernel Parameters */

		clSetKernelArg(cl->kernel, i, sizeof(cl_mem), (void *)&cl->memobj[i]);

		clEnqueueWriteBuffer(cl->command_queue, cl->memobj[i], CL_FALSE, \
			0, arg.size, arg.ptr, 0, NULL, NULL);
		clEnqueueNDRangeKernel(cl->command_queue, cl->kernel, 2, NULL, \
			&cl->work_size, NULL, 0, NULL, NULL);
		clFinish(cl->command_queue);

		// /* Execute OpenCL Kernel */
		// ret = clEnqueueTask(cl->command_queue, cl->kernel, 0, NULL,NULL);

		/* Copy results from the memory buffer */
		ret = clEnqueueReadBuffer(cl->command_queue, cl->memobj[i], CL_TRUE, 0,
			arg.size ,arg.ptr, 0, NULL, NULL);
		i++;
	}
	va_end(ap);
}

void		cl_end(t_cl *cl)
{
	cl_int		ret;
	int			i;

	ret = clFlush(cl->command_queue);
	ret = clFinish(cl->command_queue);
	ret = clReleaseKernel(cl->kernel);
	ret = clReleaseProgram(cl->program);
	i = 0;
	while (cl->memobj[i])
	{
		ret = clReleaseMemObject(cl->memobj[i]);
		i++;
	}
	ret = clReleaseCommandQueue(cl->command_queue);
	ret = clReleaseContext(cl->context);
}
