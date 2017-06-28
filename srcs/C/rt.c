/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/18 23:52:41 by agrumbac          #+#    #+#             */
/*   Updated: 2017/06/28 05:41:41 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	main_loop(t_cl *cl, t_sdl *sdl)
{
	while (1)
	{
		if (!sdl_events(sdl))
			break ;
		cl->work_size[0] = sdl->size.y;
		cl->work_size[1] = sdl->size.x;


		ft_printf("PIX = %s\n", sdl->draw_surface->pixels);


		cl_start(cl, 1, \
			(t_arg){sdl->draw_surface->pixels, sizeof(int) * sdl->size.y * sdl->size.x}
				);
		sdl_start(sdl);
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
