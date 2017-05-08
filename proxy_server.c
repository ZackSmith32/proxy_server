/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lernaean_server.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsmith <zsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/17 15:17:05 by zsmith            #+#    #+#             */
/*   Updated: 2017/02/17 15:50:04 by zsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "includes/ft_printf.h"

void					error(char *msg)
{
	perror(msg);
	exit(1);
}


int					process_stream(char *buffer, int *newsockfd)
{
	int					n;
	
	if (newsockfd < 0)
		error("ERROR on accept");
	ft_bzero(buffer, 256);
	n = read(*newsockfd, buffer, 255);
	if (n < 0)
	{
		error("ERROR reading from socket");
		return (0);
	} else if (n == 0)
		return (0);
	else
		printf("Here is the message: %s\n", buffer);
	return (1);
}

void					wait_for_stream(int socfd)
{
	
	char				buffer[256];
	int					n;
	int					newsockfd;
	struct sockaddr_in	cli_addr;
	socklen_t			cli_len;

	cli_len = sizeof(cli_addr);
	newsockfd = accept(socfd, (struct sockaddr *)&cli_addr, &cli_len);
	while (1)
	{	
		if (0 == process_stream(buffer, &newsockfd))
			break ;
		send_to_internet(buffer)
		n = write(newsockfd, "not today", 10);
		if (n < 0)
			error("ERROR writing to socket");
	}
}

int						main(int argc, char *argv[])
{
	int					sockfd;
	int					portno;
	struct sockaddr_in	serv_addr;

	if (argc < 2)
	{
		ft_printf("ERROR, no port provided\n");
		exit(1);
	}
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0)
		error("ERROR opening socket");
	ft_bzero((char *)&serv_addr, sizeof(serv_addr));
	portno = ft_atoi(argv[1]);
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(portno);
	if (bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
		error("ERROR on binding");
	listen(sockfd, 5);
	wait_for_stream(sockfd);
	return (0);
}
