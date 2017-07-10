/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/10 15:43:38 by agrumbac          #+#    #+#             */
/*   Updated: 2017/07/10 15:43:40 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "vector.h.cl"

t_vector			vector_plus(const t_vector a, const t_vector b)
{
	return ((t_vector){a.x + b.x, a.y + b.y, a.z + b.z});
}

t_vector			vector_minus(const t_vector a, const t_vector b)
{
	return ((t_vector){a.x - b.x, a.y - b.y, a.z - b.z});
}

t_vector			vector_mult(const t_vector a, const t_vector b)
{
	return ((t_vector){a.x * b.x, a.y * b.y, a.z * b.z});
}

t_vector			vector_div(const t_vector a, const t_vector b)
{
	if (!b.x || !b.y || !b.z)
	{
		dprintf(2, "Error! Division per 0 -- in vector_div()\n");
		return ((t_vector){0, 0, 0});
	}
	return ((t_vector){a.x / b.x, a.y / b.y, a.z / b.z});
}

int					vector_dot(const t_vector a, const t_vector b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_vector			vector_cross(const t_vector a, const t_vector b)
{
	return ((t_vector){y * z - z * y, x * z - z * x, x * y - y - x});
}
