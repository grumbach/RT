/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/18 23:52:41 by agrumbac          #+#    #+#             */
/*   Updated: 2017/07/05 21:54:51 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	server_loop(t_sdl *sdl, const int socket, void *objects)
{
	int			loop;
	int			active_clients;

	loop = EVENT_UPDATE;
	active_clients = 0;
	if (pthread_create(&server_thread, 0, server_connect, {sockets, &active_clients}))
		errors(ERR_SYS, "pthread_create() failed --");
	while (loop)
	{
		if (loop == EVENT_UPDATE)
		{
			//write client
			//read client
			sdl_run(sdl);
		}
		loop = sdl_events(sdl);
	}
}

static void	client_loop(t_cl *cl, const int socket)
{
	while (42)
	{
		//read server
		cl->work_size[0] = sdl->size.y;// TODO make this work must transfer data
		cl->work_size[1] = sdl->size.x;
		cl_run(cl, 1, \
			(t_arg){sdl->draw_surface->pixels, sizeof(uint32_t) * \
				sdl->size.y * sdl->size.x, CL_MEM_WRITE_ONLY});
		//write server
	}
}

static void	client()
{
	t_cl		cl;
	int			socket;

	ft_bzero(&cl, sizeof(cl));
	cl_init(&cl, "core");

	socket = socket_init(MODE_CLIENT);
	client_loop(&sdl, socket);

	close(socket);
	cl_end(&cl);
}

static void	*server(void *objects)
{
	t_sdl		sdl;
	int			socket;
	//all datastruct

	ft_bzero(&sdl, sizeof(sdl));
	sdl_init(&sdl, PROGRAM_NAME);

	socket = socket_init(MODE_SERVER);
	server_loop(&sdl, socket, objects);//send all datastruct here

	close(socket);
	sdl_end(&sdl);
	pthread_exit(NULL);
}

int			main(int ac, char **av)
{
	pthread_t		server_thread;
	t_obj			*objects;

	if (ac != 2)
		errors(ERR_USAGE, 0);
	if ((objects = parse(av[1])))
		if (pthread_create(&server_thread, 0, server, objects))
			errors(ERR_SYS, "pthread_create() failed --");

	client();
	return (EXIT_SUCCESS);
}
