/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/21 02:25:45 by agrumbac          #+#    #+#             */
/*   Updated: 2017/07/02 00:45:03 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void				cl_init(t_cl *cl, const char *kernel_name)
{
	cl_int				ret;
	ssize_t				source_size;
	char				source_str[MAX_SOURCE_SIZE];
	const char			*source_str_ptr = source_str;

	if ((ret = open(CL_FILENAME, O_RDONLY)) == -1 || \
		(source_size = read(ret, &source_str, MAX_SOURCE_SIZE)) == -1)
		errors(ERR_SYS, 0);
	close(ret);
	if (clGetDeviceIDs(NULL, CL_DEVICE, 1, &cl->device_id, NULL))
		errors(ERR_CL, "clGetDeviceIDs failure --");
	cl->context = clCreateContext(0, 1, &cl->device_id, NULL, NULL, &ret);
	ret ? errors(ERR_CL, "clCreateContext failure --") : 0;
	cl->command_queue = \
		clCreateCommandQueue(cl->context, cl->device_id, 0, &ret);
	ret ? errors(ERR_CL, "clCreateCommandQueue failure --") : 0;
	cl->program = clCreateProgramWithSource(cl->context, 1, \
		(const char **)&source_str_ptr, (const size_t *)&source_size, &ret);
	ret ? errors(ERR_CL, "clCreateProgramWithSource failure --") : 0;
	ret = clBuildProgram(cl->program, 1, &cl->device_id, CL_CC_FLAGS, 0, 0);
	ret ? cl_error_log(cl, ret) : 0;
	ret ? errors(ERR_CL, "clBuildProgram failure --") : 0;
	cl->kernel = clCreateKernel(cl->program, kernel_name, &ret);
	ret ? errors(ERR_CL, "clCreateKernel failure --") : 0;
}

static void			cl_release_old(t_cl *cl)
{
	int				i;

	i = 0;
	while (cl->variables[i])
	{
		if (clReleaseMemObject(cl->variables[i]))
			errors(ERR_CL, "clRelease failure --");
		cl->variables[i] = NULL;
		i++;
	}
}

static inline void	cl_run_args(t_cl *cl, const t_arg *arg, const int nb_arg)
{
	int			i;
	cl_int		ret;

	if (cl->variables[0])
		cl_release_old(cl);
	i = -1;
	while (++i < nb_arg)
	{
		cl->variables[i] = clCreateBuffer(cl->context, arg[i].flag, \
			arg[i].size, NULL, &ret);
		ret ? errors(ERR_CL, "clCreateBuffer failure --") : 0;
	}
	i = -1;
	while (++i < nb_arg)
		if ((arg[i].flag == CL_MEM_READ_WRITE || \
			arg[i].flag == CL_MEM_READ_ONLY) && \
			clEnqueueWriteBuffer(cl->command_queue, cl->variables[i], CL_TRUE, \
			0, arg[i].size, arg[i].ptr, 0, NULL, NULL))
			errors(ERR_CL, "clEnqueueWriteBuffer failure --");
	i = -1;
	while (++i < nb_arg)
		if ((ret = clSetKernelArg(cl->kernel, i, 8, &cl->variables[i])))
			errors(ERR_CL, "clSetKernelArg failure --");
}

void				cl_run(t_cl *cl, const int nb_arg, ...)
{
	t_arg		arg[MAX_KERNEL_ARGS];
	va_list		ap;
	int			i;

	va_start(ap, nb_arg);
	if (!nb_arg || nb_arg > MAX_KERNEL_ARGS)
		errors(ERR_CL, "cl_run: bad nb_arg --");
	i = -1;
	while (++i < nb_arg)
		arg[i] = va_arg(ap, t_arg);
	va_end(ap);
	cl_run_args(cl, arg, nb_arg);
	if (clEnqueueNDRangeKernel(cl->command_queue, cl->kernel, WORK_DIM, NULL, \
		cl->work_size, NULL, 0, NULL, NULL))
		errors(ERR_CL, "clEnqueueNDRangeKernel failure --");
	if (clFinish(cl->command_queue))
		errors(ERR_CL, "clFinish failure --");
	i = -1;
	while (++i < nb_arg)
		if ((arg[i].flag == CL_MEM_READ_WRITE || \
			arg[i].flag == CL_MEM_WRITE_ONLY) && \
			clEnqueueReadBuffer(cl->command_queue, cl->variables[i], \
			CL_TRUE, 0, arg[i].size, arg[i].ptr, 0, NULL, NULL))
			errors(ERR_CL, "clEnqueueReadBuffer failure --");
}

void				cl_end(t_cl *cl)
{
	int			i;

	if (clReleaseKernel(cl->kernel) || \
		clReleaseProgram(cl->program))
		errors(ERR_CL, "clRelease failure --");
	i = 0;
	while (cl->variables[i])
	{
		if (clReleaseMemObject(cl->variables[i]))
			errors(ERR_CL, "clRelease failure --");
		i++;
	}
	if (clReleaseCommandQueue(cl->command_queue) || \
		clReleaseContext(cl->context))
		errors(ERR_CL, "clRelease failure --");
}
