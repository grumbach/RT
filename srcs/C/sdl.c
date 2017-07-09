/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/21 15:24:34 by agrumbac          #+#    #+#             */
/*   Updated: 2017/07/09 09:15:25 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void			sdl_init_window(t_sdl *sdl)
{
	SDL_GetWindowSize(sdl->window, &sdl->size.x, &sdl->size.y);
	SDL_FreeSurface(sdl->screen);
	if (!(sdl->screen = SDL_GetWindowSurface(sdl->window)))
		errors(ERR_SDL, "SDL_GetWindowSurface failed --");
	SDL_FreeSurface(sdl->draw_surface);
	free(sdl->pixels);
	if (!(sdl->pixels = ft_memalloc(BPP * sdl->size.x * sdl->size.y)))
		errors(ERR_SYS, 0);
	if (!(sdl->draw_surface = SDL_CreateRGBSurfaceFrom((void*)sdl->pixels, \
		sdl->size.x, sdl->size.y, BPP, 4 * sdl->size.x, \
		0x000000FF, 0x0000FF00, 0x00FF0000, 0xFF000000)))
		errors(ERR_SDL, "SDL_CreateRGBSurface failed --");
}

int					sdl_events(t_sdl *sdl)
{
	if (!(SDL_WaitEvent(&sdl->event)))
		errors(ERR_SDL, "SDL_WaitEvent failed --");
	if (SDL_PollEvent(&sdl->event))
	{
		if (sdl->event.window.type == SDL_WINDOWEVENT_CLOSE || \
			sdl->event.key.keysym.sym == SDLK_ESCAPE || \
			sdl->event.type == SDL_QUIT)
			return (0);
		if (sdl->event.type == SDL_WINDOWEVENT &&
			sdl->event.window.event == SDL_WINDOWEVENT_RESIZED)
		{
			sdl_init_window(sdl);
			return (EVENT_UPDATE);
		}
	}
	return (EVENT_IDLE);
}

// const Uint8 *state = SDL_GetKeyboardState(NULL);
// SDL_GetMouseState(&x, &y);
// SDL_WarpMouseInWindow(env->win, env->ar.win_w >> 1, env->ar.win_h >> 1);
// SDL_ShowCursor(SDL_DISABLE);
// SDL_ShowCursor(SDL_ENABLE);

void				sdl_init(t_sdl *sdl, const char *window_name)
{
	if (TTF_Init() || SDL_Init(SDL_INIT_VIDEO))
		errors(ERR_SDL, "Init failed --");
	if (!(sdl->window = SDL_CreateWindow(window_name, SDL_WINDOWPOS_CENTERED, \
	SDL_WINDOWPOS_CENTERED, sdl->size.x, sdl->size.y, SDL_WINDOW_RESIZABLE)))
		errors(ERR_SDL, "SDL_CreateWindow failed --");
	SDL_SetWindowMinimumSize(sdl->window, WIN_W, WIN_H);
	sdl_init_window(sdl);
}

void				sdl_run(t_sdl *sdl)
{
	if (SDL_BlitSurface(sdl->draw_surface, NULL, sdl->screen, NULL))
		errors(ERR_SDL, "SDL_BlitSurface failed --");
	if (SDL_UpdateWindowSurface(sdl->window))
		errors(ERR_SDL, "SDL_UpdateWindowSurface failed --");
}

void				sdl_end(t_sdl *sdl)
{
	free(sdl->pixels);
	SDL_FreeSurface(sdl->screen);
	SDL_FreeSurface(sdl->draw_surface);
	SDL_DestroyWindow(sdl->window);
	SDL_Quit();
}
