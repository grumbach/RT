/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.cl                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/18 23:53:40 by agrumbac          #+#    #+#             */
/*   Updated: 2017/06/27 21:51:41 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "rt.h.cl"

static void		put_pixel(__global int* pixels, \
				const t_yx pixel, const t_yx size, const int color)
{
	pixels[pixel.x + pixel.y * size.x] = color;
}

__kernel void	core(__global int* pixels)
{
	const t_yx	pixel = (t_yx){(int)get_global_id(GLOBAL_Y), \
								(int)get_global_id(GLOBAL_X)};
	const t_yx	size = (t_yx){(int)get_global_size(GLOBAL_Y),
								(int)get_global_size(GLOBAL_X)};
	t_color		color;

	color.c.a = 0xff;
	color.c.r = (pixel.x / (float)size.x) * 0xff;
	color.c.g = (pixel.y / (float)size.y) * 0xff;
	color.c.b = 0xf;
	put_pixel(pixels, pixel, size, color.color);
}
