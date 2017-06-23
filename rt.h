/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/18 23:53:40 by agrumbac          #+#    #+#             */
/*   Updated: 2017/06/23 14:57:03 by agrumbac         ###   ########.fr       */
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
# include <stdio.h>//
# include <time.h>//
# include <errno.h>

# define WIN_H				1024
# define WIN_W				640

/*
** ********************************** OpenCL ***********************************
*/

# include <OpenCL/opencl.h>

# define MAX_SOURCE_SIZE	(0x100000)
# define CL_FILENAME		"srcs/CL/hello.cl"
# define CL_CC_FLAGS		"-I srcs/CL -cl-mad-enable -cl-fast-relaxed-math"
# define MAX_KERNEL_ARGS	5

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
	cl_mem				variables[MAX_KERNEL_ARGS + 1];
}						t_cl;

void		cl_init(t_cl *cl);
void		cl_start(t_cl *cl, const char *kernel_name, const int nb_arg, ...);
void		cl_end(t_cl *cl);

/*
** ********************************** SDL **************************************
*/

# include <SDL.h>
# include <SDL_image.h>
# include <SDL_ttf.h>

/*
** ********************************** RT ***************************************
*/

long		errors(const int err, const char *comment);

#endif
