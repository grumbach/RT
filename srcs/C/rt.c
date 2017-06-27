/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/18 23:52:41 by agrumbac          #+#    #+#             */
/*   Updated: 2017/06/27 20:01:24 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int			main(void)
{
	t_cl	cl;
	char	str[24];

	str[0] = 'N';
	str[1] = 'o';
	str[2] = 'n';
	str[3] = 'o';
	str[4] = '\0';
	ft_bzero(&cl, sizeof(cl));
	cl_init(&cl, "core");
	cl_start(&cl, 1, (t_arg){&str, 24});
	ft_printf("%s\n", str);


	str[0] = 'N';
	str[1] = 'o';
	str[2] = 'n';
	str[3] = 'o';
	str[4] = '\0';
	cl_start(&cl, 1, (t_arg){&str, 24});
	ft_printf("%s\n", str);

	cl_end(&cl);
	return (0);
}
