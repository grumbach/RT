/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/03 22:25:18 by agrumbac          #+#    #+#             */
/*   Updated: 2017/07/03 22:33:53 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_obj		*parse(const char *input)
{
	t_obj	*objects;

	objects = NULL;
	if (ft_strequ(input, PROGRAM_CLIENT))
		return (NULL);
	if (!input)//if invalid quit now!
		errors(ERR_USAGE, NULL);
	return (objects);
}
