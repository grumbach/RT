/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   easy_cl.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/28 11:54:05 by agrumbac          #+#    #+#             */
/*   Updated: 2017/06/28 12:06:10 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EASY_CL_H
# define EASY_CL_H

/*
** ********************************** OpenCL ***********************************
** MAX_SOURCE_SIZE	max size in bytes of [.cl file]
** MAX_ERR_LOG		max size in bytes of error log
** CL_FILENAME		relative path to [.cl file] containing __kernel func
** CL_CC_FLAGS		[.cl file] compilation flags (can be NULL)
** ARGS_FLAGS 		arg properties (same for all args)
** 		CL_MEM_READ_WRITE
** 		CL_MEM_WRITE_ONLY
** 		CL_MEM_READ_ONLY
** CL_DEVICE		device used
**		CL_DEVICE_TYPE_GPU
** 		CL_DEVICE_TYPE_CPU
** 		CL_DEVICE_TYPE_ALL
** MAX_KERNEL_ARGS	max numbers of args passed to __kernel func
** WORK_DIM			number of dimentions (1, 2 or 3),
** 					affects cl->work_size[WORK_DIM] : must be (size_t[WORK_DIM])
** 					filled with size values for each dimentions
** *****************************************************************************
*/

# include <OpenCL/opencl.h>

# define MAX_SOURCE_SIZE	(0x100000)
# define MAX_ERR_LOG		(10000)
# define CL_FILENAME		"srcs/CL/rt.cl"
# define CL_CC_FLAGS		"-I. -Isrcs/CL -cl-mad-enable -cl-fast-relaxed-math"
# define ARGS_FLAGS			CL_MEM_READ_WRITE
# define CL_DEVICE			CL_DEVICE_TYPE_ALL
# define MAX_KERNEL_ARGS	5
# define WORK_DIM			2

typedef struct			s_arg
{
	void				*ptr;
	size_t				size;
}						t_arg;

typedef struct			s_cl
{
	size_t				work_size[WORK_DIM];
	cl_context			context;
	cl_command_queue	command_queue;
	cl_program			program;
	cl_kernel			kernel;
	cl_device_id		device_id;
	cl_mem				variables[MAX_KERNEL_ARGS + 1];
}						t_cl;

/*
** ********************************** functions ********************************
** void		cl_init(t_cl *cl);
** 					initialize cl program
** void		cl_run(t_cl *cl, const char *kernel_name, const int nb_arg, ...);
**					args of type (t_arg){void*, size_t}; ie:
** 					cl_run(cl, "my_kern_func", 1, (t_arg){ptr, 1024});
** 					call __kernel function in [.cl file] with arguments:
** 					__kernel void kernel_name(__global ...)
** void		cl_end(t_cl *cl);
** 					terminate and free all cl environment
** *****************************************************************************
*/

void					cl_init(t_cl *cl, const char *kernel_name);
void					cl_run(t_cl *cl, const int nb_arg, ...);
void					cl_end(t_cl *cl);

/*
** ********************************** errors ***********************************
*/

void					cl_error_log(t_cl *cl, const cl_int error_code);

#endif
