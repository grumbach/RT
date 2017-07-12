/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/10 22:54:41 by agrumbac          #+#    #+#             */
/*   Updated: 2017/07/10 22:54:43 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "hit.h.cl"

int			hit_sphere(const void *sphere, const t_ray *ray)
{
	t_vector	oc = ray->origin - ((t_sphere*)sphere)->center;
	float		a = dot(ray->direction, ray->direction);
	float		b = 2 * dot(oc, ray->direction);
	float		c = dot(oc, oc) - ((t_sphere*)sphere)->radius *
									((t_sphere*)sphere)->radius;
	float		d = b * b - 4 * a * c;
	return (d > 0);
}
