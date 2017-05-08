/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lernaean_client.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsmith <zsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/17 15:21:15 by zsmith            #+#    #+#             */
/*   Updated: 2017/02/17 15:22:10 by zsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include "./includes/ft_printf.h"

void					error(char *msg)
{
	perror(msg);
	exit(0);
}

void					get_message(int sockfd, struct sockaddr_in serv_addr)
{
	int					n;
	char				buffer[256];

	if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
		error("ERROR connecting");
	ft_printf("Please enter the message: ");
	ft_bzero(buffer, 256);
	fgets(buffer, 255, stdin);
	n = write(sockfd, buffer, strlen(buffer));
	if (n < 0)
		error("ERROR writing to socket");
	ft_bzero(buffer, 256);
	sleep(10);
	strcpy(buffer, "mic check\n");
	n = write(sockfd, buffer, strlen(buffer));
	n = read(sockfd, buffer, 255);
	if (n < 0)
		error("ERROR reading from socket");
	ft_printf("%s\n", buffer);
}

int						main(int argc, char **argv)
{
	int					sockfd;
	struct sockaddr_in	serv_addr;
	struct hostent		*server;

	if (argc < 3)
	{
		ft_printf("usage %s hostname port\n", argv[0]);
		exit(0);
	}
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0)
		error("ERROR opening socket");
	server = gethostbyname(argv[1]);
	if (server == NULL)
	{
		ft_printf("ERROR, no such host\n");
		exit(0);
	}
	ft_bzero((char *)&serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	ft_memcpy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr,
		server->h_length);
	serv_addr.sin_port = htons(atoi(argv[2]));
	get_message(sockfd, serv_addr);
	return (0);
}
