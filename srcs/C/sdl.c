/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/21 15:24:34 by agrumbac          #+#    #+#             */
/*   Updated: 2017/06/28 05:39:37 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void			sdl_init_window(t_sdl *sdl)
{
	if (!(sdl->screen = SDL_GetWindowSurface(sdl->window)))
		errors(2, "SDL_GetWindowSurface failed --");
	SDL_FreeSurface(sdl->draw_surface);
	if (!(sdl->draw_surface = SDL_CreateRGBSurface(0, sdl->size.x, sdl->size.y,
		32, 0x000000FF, 0x0000FF00, 0x00FF0000, 0xFF000000)))
		errors(2, "SDL_CreateRGBSurface failed --");
}

int					sdl_events(t_sdl *sdl)
{
	if (SDL_PollEvent(&sdl->event))
	{
		if (sdl->event.window.type == SDL_WINDOWEVENT_CLOSE || \
			sdl->event.key.keysym.sym == SDLK_ESCAPE || \
			sdl->event.type == SDL_QUIT)
			return (0);
		if (sdl->event.type == SDL_WINDOWEVENT_RESIZED)
			sdl_init_window(sdl);
	}
	return (1);
}

// const Uint8 *state = SDL_GetKeyboardState(NULL);
// SDL_GetMouseState(&x, &y);
// SDL_WarpMouseInWindow(env->win, env->ar.win_w >> 1, env->ar.win_h >> 1);
// SDL_ShowCursor(SDL_DISABLE);
// SDL_ShowCursor(SDL_ENABLE);

void				sdl_init(t_sdl *sdl, const char *window_name)
{
	if (TTF_Init() || SDL_Init(SDL_INIT_VIDEO))
		errors(2, "Init failed --");
	if (!(sdl->window = SDL_CreateWindow(window_name, 0, 0, \
		sdl->size.x, sdl->size.y, SDL_WINDOW_RESIZABLE)))
		errors(2, "SDL_CreateWindow failed --");
	SDL_SetWindowMinimumSize(sdl->window, WIN_W, WIN_H);
	sdl_init_window(sdl);
	if (SDL_BlitSurface(sdl->draw_surface, NULL, sdl->screen, NULL))
		errors(2, "SDL_BlitSurface failed --");
}

void				sdl_start(t_sdl *sdl)
{
	if (SDL_BlitSurface(sdl->draw_surface, NULL, sdl->screen, NULL))
		errors(2, "SDL_BlitSurface failed --");
	if (SDL_UpdateWindowSurface(sdl->window))
		errors(2, "SDL_UpdateWindowSurface failed --");
}

void				sdl_end(t_sdl *sdl)
{
	SDL_FreeSurface(sdl->screen);
	SDL_FreeSurface(sdl->draw_surface);
	SDL_DestroyWindow(sdl->window);
	SDL_Quit();
}
