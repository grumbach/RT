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

__kernel void core(__global int* string)
{
	const t_yx	pixel = (t_yx){(int)get_global_id(0), (int)get_global_id(1)};
	const t_yx	size = (t_yx){(int)get_global_size(0), (int)get_global_size(1)};

	printf("[y %d, x %d] -- ", pixel.y, pixel.x);
	printf("{y %d, x %d}\n", size.y, size.x);
}
