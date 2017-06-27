/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/18 23:53:40 by agrumbac          #+#    #+#             */
/*   Updated: 2017/06/27 19:57:28 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

/*
** ********************************** Global ***********************************
*/

# define PROGRAM_NAME		"rtv1"

# include "libft.h"

# include <math.h>
# include <fcntl.h>
# include <errno.h>

# define WIN_H				1024
# define WIN_W				640

/*
** ********************************** OpenCL ***********************************
** MAX_SOURCE_SIZE	max size in bytes of [.cl file]
** MAX_ERR_LOG		max size in bytes of error log
** CL_FILENAME		relative path to [.cl file] containing __kernel func
** CL_CC_FLAGS		[.cl file] compilation flags (can be NULL)
** MAX_KERNEL_ARGS	max numbers of args passed to __kernel func
** ARGS_FLAGS 		arg properties (same for all args) ie:
** 		CL_MEM_READ_WRITE
** 		CL_MEM_WRITE_ONLY	//not implemented yet
** 		CL_MEM_READ_ONLY	//not implemented yet
** CL_DEVICE		device used
**		CL_DEVICE_TYPE_GPU
** 		CL_DEVICE_TYPE_CPU
** 		CL_DEVICE_TYPE_ALL
** DEFAULT_THREADS	default number of threads, pixel grid
**
** ********************************** functions ********************************
** void	cl_init(t_cl *cl);
** 					initialize cl program
** void	cl_start(t_cl *cl, const char *kernel_name, const int nb_arg, ...);
**					args of type (t_arg){void*, size_t}; ie:
** 					cl_start(cl, "my_kern_func", 1, (t_arg){ptr, 1024});
** 					call __kernel function in [.cl file] with arguments:
** 					__kernel void kernel_name(__global ...)
** void	cl_end(t_cl *cl);
** 					terminate and free all cl environment
** *****************************************************************************
*/

# include <OpenCL/opencl.h>

# define MAX_SOURCE_SIZE	(0x100000)
# define MAX_ERR_LOG		(10000)
# define CL_FILENAME		"srcs/CL/hello.cl"
# define CL_CC_FLAGS		"-I. -cl-mad-enable -cl-fast-relaxed-math"
# define CL_DEVICE			CL_DEVICE_TYPE_ALL
# define MAX_KERNEL_ARGS	5
# define ARGS_FLAGS			CL_MEM_READ_WRITE
# define DEFAULT_THREADS	(WIN_H * WIN_W)

typedef struct			s_arg
{
	void				*ptr;
	size_t				size;
}						t_arg;

typedef struct			s_cl
{
	size_t				work_size;
	cl_context			context;
	cl_command_queue	command_queue;
	cl_program			program;
	cl_kernel			kernel;
	cl_device_id		device_id;
	cl_mem				variables[MAX_KERNEL_ARGS + 1];
}						t_cl;

void		cl_init(t_cl *cl, const char *kernel_name);
void		cl_start(t_cl *cl, const int nb_arg, ...);
void		cl_end(t_cl *cl);

/*
** ********************************** SDL **************************************
*/

# include <SDL.h>
# include <SDL_image.h>
# include <SDL_ttf.h>

/*
** ********************************** errors ***********************************
*/

void		cl_error_log(t_cl *cl, const cl_int error_code);
long		errors(const int err, const char *comment);

/*
** ********************************** RT ***************************************
*/

#endif
