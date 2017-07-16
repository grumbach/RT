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

int			hit_sphere(const void *sphere, const t_ray *ray, t_hit *record)
{
	const t_vector	oc = ray->origin - ((t_sphere*)sphere)->center;
	const float		a = dot(ray->direction, ray->direction);
	const float		b = dot(oc, ray->direction);
	const float		c = dot(oc, oc) - ((t_sphere*)sphere)->radius *
									((t_sphere*)sphere)->radius;
	const float		d = b * b - a * c;
	float			t;

	if (d > 0)
	{
		if ((t = (-b - sqrt(b * b - a * c)) / a) < 0)
			if ((t = (-b + sqrt(b * b - a * c)) / a) < 0)
				return (0);
		record->t = t;
		record->point = unit_vector(ray->origin + t * ray->direction);
		record->normal = (record->point - ((t_sphere*)sphere)->center) / \
						((t_sphere*)sphere)->radius;
		return (1);
	}
	return (0);
}

// int			hit_cone(const void *cone, const t_ray *ray)
// {
// 	const t_vector	co = vector(((t_cone*)cone)->tip, ray->origin);
// 	const float		t = pow(cos(((t_cone*)cone)->angle), 2);
// 	const float		a = pow(dot(ray->direction, ((t_cone*)cone)->axis), 2) - t;
// 	const float		b = 2 * (dot(ray->direction, ((t_cone*)cone)->axis) * \
// 					dot(co, ((t_cone*)cone)->axis) - \
// 					dot(ray->direction, co) * t);
// 	const float		c = pow(dot(co, ((t_cone*)cone)->axis), 2) - dot(co, co) * t;
// 	const float		d = b * b - 4 * a * c;
//
// 	return (d >= 0);
// }
