/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/18 23:52:41 by agrumbac          #+#    #+#             */
/*   Updated: 2017/06/26 23:42:26 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

long		errors(const int err, const char *comment)
{
	ft_putstr_fd("RT: ", 2);
	if (comment)
	{
		ft_putstr_fd(comment, 2);
		ft_putstr_fd(" ", 2);
	}
	if (err == 0)
		ft_putendl_fd(strerror(errno), 2);
	else if (err == 1)
		ft_putstr_fd("OpenCL failure\n", 2);
	exit(EXIT_FAILURE);
	return (0);
}

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
	cl_init(&cl);
	cl_start(&cl, "core", 1, (t_arg){&str, 24});
	ft_printf("%s\n", str);
	cl_end(&cl);
	return (0);
}
