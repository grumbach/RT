/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.h.cl                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/12 10:38:58 by agrumbac          #+#    #+#             */
/*   Updated: 2017/07/12 10:39:00 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HIT_H_CL
# define HIT_H_CL

# include "vector.h.cl"

/*
** ********************************** shapes ***********************************
*/

# define SPHERE		1
# define PLANE		2
# define TRIANGLE	3

typedef struct		s_sphere
{
	t_vector		center;
	float			radius;
}					t_sphere;

typedef struct		s_plane
{
	t_vector		point;
	t_vector		normal;
}					t_plane;

typedef struct		s_cone
{
	t_vector		tip;
	t_vector		axis;
	float			angle;
}					t_cone;

typedef struct		s_triangle
{
	t_vector		a;
	t_vector		b;
	t_vector		c;
}					t_triangle;

/*
** ********************************** ray **************************************
*/

typedef struct			s_ray
{
	t_vector			origin;
	t_vector			direction;
}						t_ray;

/*
** ********************************** hit **************************************
*/

typedef struct			s_hit
{
	float				t;
	t_vector			point;
	t_vector			normal;
}						t_hit;

int			hit_sphere(const void *sphere, const t_ray *ray, t_hit *record);
int			hit_plane(const void *plane, const t_ray *ray, t_hit *record);
int			hit_cone(const void *cone, const t_ray *ray, t_hit *record);
int			hit_cylinder(const void *cylinder, const t_ray *ray, t_hit *record);
int			hit_triangle(const void *triangle, const t_ray *ray, t_hit *record);

#endif
