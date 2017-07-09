/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   easy_socket.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/02 00:07:00 by agrumbac          #+#    #+#             */
/*   Updated: 2017/07/05 21:55:00 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EASY_SOCKET_H
# define EASY_SOCKET_H

# include <pthread.h>
# include <sys/socket.h>
# include <sys/types.h>
# include <netinet/in.h>
# include <netdb.h>

# define PORT			4242
# define CLIENT_LIMIT	5

# define MODE_SERVER	1
# define MODE_CLIENT	0

# define ORDER_PING		0
# define ORDER_WORK		1
# define ORDER_STOP		2

/*
** ********************************** functions ********************************
** void		socket_init(const int mode);
** 					initialize sockets with mode :
** 							MODE_SERVER
** 							MODE_CLIENT
** *****************************************************************************
*/

void		socket_init(const int mode);

void		*server_connect(void *);

void		server_send_order(const int socket, const int order, int data);

int			client_get_order();
void		client_done();

#endif
