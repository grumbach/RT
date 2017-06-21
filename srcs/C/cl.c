/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/21 02:25:45 by agrumbac          #+#    #+#             */
/*   Updated: 2017/06/21 12:09:08 by agrumbac         ###   ########.fr       */
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

	/* Load the source code containing the kernel*/
	if ((fd = open(CL_FILENAME, O_RDONLY)) == -1)
		errors(0, 0);
	if ((source_size = read(fd, &source_str, MAX_SOURCE_SIZE)) == -1)
		errors(0, 0);
	close(fd);

	/* Get Platform and Device Info */
	ret = clGetPlatformIDs(1, &platform_id, &ret_num_platforms);
	ret = clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_DEFAULT, 1, &device_id, &ret_num_devices);
	/* Create OpenCL context */
	cl->context = clCreateContext(NULL, 1, &device_id, NULL, NULL, &ret);
	/* Create Command Queue */
	cl->command_queue = clCreateCommandQueue(cl->context, device_id, 0, &ret);
	/* Create Kernel Program from the source */
	cl->program = clCreateProgramWithSource(cl->context, 1, (const char **)&source_str_ptr,
	(const size_t *)&source_size, &ret);
	/* Build Kernel Program */
	ret = clBuildProgram(cl->program, 1, &device_id, NULL, NULL, NULL);

}

void		cl_start(t_cl *cl, const char *kernel_name, const int nb_args, ...)
{
	cl_int		ret;
	t_cl_arg	arg;
	va_list		ap;
	int			i;

	if (!nb_args || nb_args > MAX_KERNEL_ARGS)
		errors(1, "cl_start: bad nb_args --");
	va_start(ap, nb_args);
	i = 0;
	while (i < nb_args)
	{
		arg = va_arg(ap, t_cl_arg);
		/* Create Memory Buffer */
		cl->memobj = clCreateBuffer(cl->context, CL_MEM_READ_WRITE, arg.size, NULL, &ret);
		i++;
	}

	/* Create OpenCL Kernel */
	cl->kernel = clCreateKernel(cl->program, kernel_name, &ret);

	/* Set OpenCL Kernel Parameters */
	ret = clSetKernelArg(cl->kernel, i, sizeof(cl_mem), (void *)&cl->memobj);

	/* Execute OpenCL Kernel */
	ret = clEnqueueTask(cl->command_queue, cl->kernel, 0, NULL,NULL);

	/* Copy results from the memory buffer */
	ret = clEnqueueReadBuffer(cl->command_queue, cl->memobj, CL_TRUE, 0,
		arg.size ,arg.arg, 0, NULL, NULL);
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
