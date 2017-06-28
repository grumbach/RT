/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/18 23:52:41 by agrumbac          #+#    #+#             */
/*   Updated: 2017/06/28 13:51:46 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	main_loop(t_cl *cl, t_sdl *sdl)
{
	int		loop;

	loop = EVENT_UPDATE;
	while (loop)
	{
		if (loop == EVENT_UPDATE)
		{
			cl->work_size[0] = sdl->size.y;// TODO optimize this
			cl->work_size[1] = sdl->size.x;
			cl_run(cl, 1, \
				(t_arg){sdl->draw_surface->pixels, sizeof(uint32_t) * \
					sdl->size.y * sdl->size.x, CL_MEM_WRITE_ONLY});
			sdl_run(sdl);
		}
		loop = sdl_events(sdl);
	}
}

int			main(void)
{
	t_cl	cl;
	t_sdl	sdl;

	ft_bzero(&cl, sizeof(cl));
	ft_bzero(&sdl, sizeof(sdl));

	cl_init(&cl, "core");
	sdl_init(&sdl, PROGRAM_NAME);

	main_loop(&cl, &sdl);

	cl_end(&cl);
	sdl_end(&sdl);
	return (EXIT_SUCCESS);
}
