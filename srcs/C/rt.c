/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/18 23:52:41 by agrumbac          #+#    #+#             */
/*   Updated: 2017/07/12 15:07:19 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	main_loop(t_cl *cl, t_sdl *sdl)
{
	t_cam	cam;
	int		loop;

	cam = (t_cam){(t_vector){0, 0, 0}, (t_vector){0, 0, -1}, \
		(t_vector){0, 1, 0}, 90, sdl->size.x / (float)sdl->size.y};
	loop = EVENT_UPDATE;
	while (loop)
	{
		if (loop == EVENT_UPDATE)
		{
			cl_run(cl, (size_t[WORK_DIM]){sdl->size.y, sdl->size.x}, 2, \
				(t_arg){sdl->draw_surface->pixels, sizeof(uint32_t) * \
					sdl->size.y * sdl->size.x, CL_MEM_WRITE_ONLY}, \
				(t_arg){&cam, 100, CL_MEM_READ_ONLY});
			sdl_run(sdl);
		}
		loop = sdl_events(sdl, &cam);
	}
}

int			main(void)
{
	t_cl	cl;
	t_sdl	sdl;

	ft_bzero(&cl, sizeof(cl));
	ft_bzero(&sdl, sizeof(sdl));

	cl_init(&cl, 0);
	sdl_init(&sdl, PROGRAM_NAME);

	main_loop(&cl, &sdl);

	cl_end(&cl);
	sdl_end(&sdl);
	return (EXIT_SUCCESS);
}
