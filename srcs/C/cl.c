/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/21 02:25:45 by agrumbac          #+#    #+#             */
/*   Updated: 2017/06/23 07:47:59 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		cl_init(t_cl *cl)
{
	cl_device_id 		device_id = NULL;
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
	if (clGetDeviceIDs(NULL, CL_DEVICE_TYPE_GPU, 1, &device_id, NULL))
		errors(1, "clGetDeviceIDs failure --");
	cl->context = clCreateContext(0, 1, &device_id, NULL, NULL, &ret);
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
	t_arg		arg[MAX_KERNEL_ARGS];
	va_list		ap;
	int			i;

	if (!nb_args || nb_args > MAX_KERNEL_ARGS)
		errors(1, "cl_start: bad nb_args --");
	va_start(ap, nb_args);
	i = 0;
	while (i < nb_args)
		arg[i] = va_arg(ap, t_arg);


	cl->kernel = clCreateKernel(cl->program, kernel_name, &ret);
	ret ? errors(1, "clCreateKernel failure --") : 0;

	i = 0;
	while (i < nb_args)
	{
		cl->variables[i] = clCreateBuffer(cl->context, CL_MEM_READ_WRITE, arg[i].size, NULL, &ret);
		ret ? errors(1, "clCreateBuffer failure --") : 0;
		i++;
	}


	i = 0;
	while (i < nb_args)
	{
		clEnqueueWriteBuffer(cl->command_queue, cl->variables[i], CL_TRUE, \
			0, arg[i].size, arg[i].ptr, 0, NULL, NULL);
		i++;
	}


	i = 0;
	while (i < nb_args)
	{
		clSetKernelArg(cl->kernel, i, arg[i].size, (void *)&cl->variables[i]);
		i++;
	}

	clEnqueueNDRangeKernel(cl->command_queue, cl->kernel, 2, NULL, \
		&cl->work_size, NULL, 0, NULL, NULL);
	clFinish(cl->command_queue);


	i = 0;
	while (i < nb_args)
	{
		ret = clEnqueueReadBuffer(cl->command_queue, cl->variables[i], CL_TRUE, 0,
			arg[i].size ,arg[i].ptr, 0, NULL, NULL);
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
	while (cl->variables[i])
	{
		ret = clReleaseMemObject(cl->variables[i]);
		i++;
	}
	ret = clReleaseCommandQueue(cl->command_queue);
	ret = clReleaseContext(cl->context);
}
