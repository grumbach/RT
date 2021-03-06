/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/12 12:49:22 by agrumbac          #+#    #+#             */
/*   Updated: 2017/07/12 15:17:36 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "easy_sdl.h"
#include "rt.h"

static int			sdl_keyboard(t_cam *cam)
{
	const Uint8		*state = SDL_GetKeyboardState(NULL);

	if (state[SDL_SCANCODE_W])
		cam->origin.z -= 0.1;
	if (state[SDL_SCANCODE_S])
		cam->origin.z += 0.1;
	if (state[SDL_SCANCODE_A])
		cam->origin.x += 0.1;
	if (state[SDL_SCANCODE_D])
		cam->origin.x -= 0.1;
	if (state[SDL_SCANCODE_S] || state[SDL_SCANCODE_W] || \
		state[SDL_SCANCODE_A] || state[SDL_SCANCODE_D])
		return (1);
	return (0);
}

int					sdl_events(t_sdl *sdl, t_cam *cam)
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
			cam->aspect = sdl->size.x / (float)sdl->size.y;
			return (EVENT_UPDATE);
		}
		if (sdl_keyboard(cam))
			return (EVENT_UPDATE);
	}
	return (EVENT_IDLE);
}

// SDL_GetMouseState(&x, &y);
// SDL_WarpMouseInWindow(env->win, env->ar.win_w >> 1, env->ar.win_h >> 1);
// SDL_ShowCursor(SDL_DISABLE);
// SDL_ShowCursor(SDL_ENABLE);
