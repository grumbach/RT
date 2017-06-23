/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/21 02:25:45 by agrumbac          #+#    #+#             */
/*   Updated: 2017/06/23 17:42:03 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void				cl_init(t_cl *cl)
{
	cl_device_id		device_id;
	cl_int				ret;
	ssize_t				source_size;
	char				source_str[MAX_SOURCE_SIZE];
	const char			*source_str_ptr = source_str;

	device_id = NULL;
	if ((ret = open(CL_FILENAME, O_RDONLY)) == -1)
		errors(0, 0);
	if ((source_size = read(ret, &source_str, MAX_SOURCE_SIZE)) == -1)
		errors(0, 0);
	close(ret);
	if (clGetDeviceIDs(NULL, CL_DEVICE_TYPE_GPU, 1, &device_id, NULL))
		errors(1, "clGetDeviceIDs failure --");
	cl->context = clCreateContext(0, 1, &device_id, NULL, NULL, &ret);
	ret ? errors(1, "clCreateContext failure --") : 0;
	cl->command_queue = clCreateCommandQueue(cl->context, device_id, 0, &ret);
	ret ? errors(1, "clCreateCommandQueue failure --") : 0;
	cl->program = clCreateProgramWithSource(cl->context, 1, \
		(const char **)&source_str_ptr, (const size_t *)&source_size, &ret);
	ret ? errors(1, "clCreateProgramWithSource failure --") : 0;
	if (clBuildProgram(cl->program, 1, &device_id, CL_CC_FLAGS, NULL, NULL))
		errors(1, "clBuildProgram failure --");
	cl->work_size = WIN_H * WIN_W;
}

static inline void	cl_start_args(t_cl *cl, const t_arg *arg, const int nb_arg)
{
	int			i;
	cl_int		ret;

	i = -1;
	while (++i < nb_arg)
	{
		cl->variables[i] = clCreateBuffer(cl->context, ARGS_FLAGS, \
			arg[i].size, NULL, &ret);
		ret ? errors(1, "clCreateBuffer failure --") : 0;
	}
	i = -1;
	while (++i < nb_arg)
		if (clEnqueueWriteBuffer(cl->command_queue, cl->variables[i], CL_TRUE, \
			0, arg[i].size, arg[i].ptr, 0, NULL, NULL))
			errors(1, "clEnqueueWriteBuffer failure --");
	i = -1;
	while (++i < nb_arg)
		if ((ret = clSetKernelArg(cl->kernel, i, 8, &cl->variables[i])))
			errors(1, "clSetKernelArg failure --");
}

void				cl_start(t_cl *cl, const char *kernel_name, \
					const int nb_arg, ...)
{
	cl_int		ret;
	t_arg		arg[MAX_KERNEL_ARGS];
	va_list		ap;
	int			i;

	va_start(ap, nb_arg);
	if (!nb_arg || nb_arg > MAX_KERNEL_ARGS)
		errors(1, "cl_start: bad nb_arg --");
	i = -1;
	while (++i < nb_arg)
		arg[i] = va_arg(ap, t_arg);
	va_end(ap);
	cl->kernel = clCreateKernel(cl->program, kernel_name, &ret);
	ret ? errors(1, "clCreateKernel failure --") : 0;
	cl_start_args(cl, arg, nb_arg);
	if (clEnqueueNDRangeKernel(cl->command_queue, cl->kernel, 1, NULL, \
		&cl->work_size, NULL, 0, NULL, NULL))
		errors(1, "clEnqueueNDRangeKernel failure --");
	if (clFinish(cl->command_queue))
		errors(1, "clFinish failure --");
	i = -1;
	while (++i < nb_arg)
		if (clEnqueueReadBuffer(cl->command_queue, cl->variables[i], \
			CL_TRUE, 0, arg[i].size, arg[i].ptr, 0, NULL, NULL))
			errors(1, "clEnqueueReadBuffer failure --");
}

void				cl_end(t_cl *cl)
{
	int			i;

	if (clReleaseKernel(cl->kernel) || \
		clReleaseProgram(cl->program))
		errors(1, "clRelease failure --");
	i = 0;
	while (cl->variables[i])
	{
		if (clReleaseMemObject(cl->variables[i]))
			errors(1, "clRelease failure --");
		i++;
	}
	if (clReleaseCommandQueue(cl->command_queue) || \
		clReleaseContext(cl->context))
		errors(1, "clRelease failure --");
}
