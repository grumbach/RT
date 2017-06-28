/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   easy_sdl.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/28 11:55:45 by agrumbac          #+#    #+#             */
/*   Updated: 2017/06/28 12:06:25 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EASY_SDL_H
# define EASY_SDL_H

/*
** ********************************** SDL **************************************
** BPP				BytesPerPixel : is 32 for (uint32_t*)sdl->pixels
**
** ********************************** functions ********************************
** void		sdl_init(t_sdl *sdl, const char *window_name);
** 					initialize sdl window
** void		sdl_run(t_sdl *sdl);
** 					draw sdl->pixels to sdl->screen of sdl->window
** void		cl_end(t_cl *cl);
** 					terminate and free all sdl environment
** int		sdl_events(t_sdl *sdl);
** 					fetch sdl events returns a status from :
** 					EVENT_STOP, EVENT_IDLE, EVENT_UPDATE
** *****************************************************************************
*/

# include <SDL.h>
# include <SDL_image.h>
# include <SDL_ttf.h>

# define EVENT_STOP			0
# define EVENT_IDLE			1
# define EVENT_UPDATE		2

# define BPP				32

typedef struct			s_yx
{
	int					y;
	int					x;
}						t_yx;

typedef struct			s_sdl
{
	SDL_Window			*window;
	SDL_Surface			*screen;
	SDL_Surface			*draw_surface;
	SDL_Event			event;
	t_yx				size;
	uint32_t			*pixels;
}						t_sdl;

void					sdl_init(t_sdl *sdl, const char *window_name);
void					sdl_run(t_sdl *sdl);
void					sdl_end(t_sdl *sdl);
int						sdl_events(t_sdl *sdl);

#endif
