/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h.cl                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/18 23:53:40 by agrumbac          #+#    #+#             */
/*   Updated: 2017/06/27 22:00:32 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H_CL
# define RT_H_CL

/*
** ********************************** geometry *********************************
*/

# include "vector.h.cl"

/*
** ********************************** data *************************************
*/

# define GLOBAL_X	1
# define GLOBAL_Y	0

typedef struct			s_yx
{
	int					y;
	int					x;
}						t_yx;

typedef union 			s_color
{
	unsigned int		color;
	struct				s_c
	{
		unsigned char	r;
		unsigned char	g;
		unsigned char	b;
		unsigned char	a;
	}					c;
}						t_color;

#endif
