/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socket.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/02 00:01:24 by agrumbac          #+#    #+#             */
/*   Updated: 2017/07/05 21:46:49 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			socket_init(const int mode)
{
	const int			sockets = socket(PF_INET, SOCK_STREAM, 0);
	struct sockaddr_in	address;

	ft_bzero(&address, sizeof(address));
	address.sin_family = AF_INET;
	address.sin_port = htons(PORT);
	address.sin_addr.s_addr = INADDR_ANY;
	if (mode == MODE_CLIENT)
	{
		if (connect(sockets, (struct sockaddr *)&address, sizeof(address)) == -1)
			errors(ERR_SYS, "connect() failed --");
	}
	else
	{
		if (bind(sockets, (struct sockaddr *)&address, sizeof(address)))
			errors(ERR_SYS, "bind() failed --");
		if (listen(sockets, CLIENT_LIMIT))
			errors(ERR_SYS, "listen() failed --");
	}
	return (sockets);
}


{
	read(sockets, buffer, size);
}
{
	// thread();
	client_len = sizeof(client_address);
	while (42)
	{
		if ((client_socket = accept(sockets, \
		(struct sockaddr *)&client_address, &client_len)) == -1)
			errors(ERR_SYS, "accept() failed --");
		while (42)
		{
			// thread();
			write(client_socket, buffer, size);
			read(client_socket, buffer, size);
		}
	}
	close(client_socket);
}
