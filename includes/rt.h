/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/18 23:53:40 by agrumbac          #+#    #+#             */
/*   Updated: 2017/07/12 15:06:54 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

/*
** ********************************** Global ***********************************
*/

# define PROGRAM_NAME		"rtv1"

# include <math.h>
# include <fcntl.h>
# include <errno.h>

/*
** ********************************** Local ************************************
*/


# include "libft.h"
# include "easy_cl.h"
# include "easy_sdl.h"

# define WIN_H				640
# define WIN_W				1024

/*
** ********************************** errors ***********************************
*/

# define ERR_SYS			0
# define ERR_CL				1
# define ERR_SDL			2
# define ERR_USAGE			3

/*
** ********************************** camera ***********************************
** int		sdl_events(t_sdl *sdl, );
** 					fetch sdl events returns a status from :
** 					EVENT_STOP, EVENT_IDLE, EVENT_UPDATE
** *****************************************************************************
*/

# define EVENT_STOP			0
# define EVENT_IDLE			1
# define EVENT_UPDATE		2

typedef struct			s_vector
{
	float				x;
	float				y;
	float				z;
	uint32_t : 32;
}						t_vector;

typedef struct			s_cam
{
	t_vector			origin;
	t_vector			direction;
	t_vector			up;
	float				fov;
	float				aspect;
	uint64_t : 64;
}						t_cam;

int						sdl_events(t_sdl *sdl, t_cam *cam);

/*
** *****************************************************************************
*/

long					errors(const int err, const char *comment);

#endif
