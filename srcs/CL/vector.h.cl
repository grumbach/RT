/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/10 15:47:51 by agrumbac          #+#    #+#             */
/*   Updated: 2017/07/10 15:47:55 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H_CL
# define VECTOR_H_CL

typedef struct		s_vector
{
	int				x;
	int				y;
	int				z;
}					t_vector;

t_vector			vector_plus(t_vector a, t_vector b);
t_vector			vector_minus(t_vector a, t_vector b);
t_vector			vector_mult(t_vector a, t_vector b);
t_vector			vector_div(t_vector a, t_vector b);

int					vector_dot(t_vector a, t_vector b);
t_vector			vector_cross(t_vector a, t_vector b);

#endif
