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
# include "vector.cl"
# include "hit.cl"

static void		put_pixel(__global uint* pixels, \
				const t_yx pixel, const t_yx size, const int color)
{
	pixels[pixel.x + pixel.y * size.x] = color;
}

static uint		get_color(const void *obj, const t_ray ray)
{
	t_color		color;
	t_hit		record;

	color.color = 0xffaaaaaa;
	if (hit_sphere(obj, &ray, &record))
	{
		color.c.r = (0.5 * (record.normal.x + 1)) * 0xff;
		color.c.g = (0.5 * (record.normal.y + 1)) * 0xff;
		color.c.b = (0.5 * (record.normal.z + 1)) * 0xff;
	}
	return (color.color);
}

static t_ray	get_ray(__constant t_cam *cam, const float s, const float t)
{
	float		theta = cam->fov * M_PI / 180;
	float		half_height = tan(theta / 2);
	float		half_width = cam->aspect * half_height;
	t_vector	w = unit_vector(cam->origin - cam->direction);
	t_vector	u = unit_vector(cross(cam->up, w));
	t_vector	v = cross(w, u);
	return ((t_ray){cam->origin, \
		(cam->origin - half_width * u - half_height * v - w) + \
		s * (2 * half_width * u) + t * (2 * half_height * v) - cam->origin});
}

__kernel void	core(__global uint* pixels, __constant t_cam *cam)
{
	const t_yx	pixel = (t_yx){(int)get_global_id(GLOBAL_Y), \
								(int)get_global_id(GLOBAL_X)};
	const t_yx	size = (t_yx){(int)get_global_size(GLOBAL_Y), \
								(int)get_global_size(GLOBAL_X)};
	const t_sphere obj = (t_sphere){(t_vector){0, 0, -1}, 0.5};//tmp
	// const t_cone obj = (t_cone){(t_vector){0, 0, -100}, (t_vector){0, 0, -0.5}, 0.5};

	put_pixel(pixels, pixel, size, get_color(&obj, get_ray(cam, \
		pixel.x / (float)size.x, pixel.y / (float)size.y)));
}
