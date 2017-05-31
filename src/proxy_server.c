/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proxy_server.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mba <mba@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/17 15:17:05 by zsmith            #+#    #+#             */
/*   Updated: 2017/05/31 15:45:53 by mba              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <proxy_server.h>

void	error(char *msg)
{
	perror(msg);
	exit(1);
}

/*
 *	Receive data stream from client
 *		> remove client specific information
 *		> construct outgoing request
 */

int		process_stream(char *buffer, int *newsockfd)
{
	int					n;

	if (newsockfd < 0)
		error("ERROR: on accept");
	bzero(buffer, STREAM_SIZE + 1);
	n = read(*newsockfd, buffer, STREAM_SIZE);
	if (n < 0)
	{
		error("ERROR: reading from socket");
		return (0);
	}
	else if (n == 0)
		return (0);
	else
		printf("Here is the message: \n%s", buffer);
	return (1);
}

/*
 *	Create infinite loop that will continue reading from client stream
 *		until client closes the stream.
 *
 */

void	wait_for_stream(int socfd)
{

	char				buffer[STREAM_SIZE + 1];
	int					n;
	int					newsockfd;
	struct sockaddr_in	cli_addr;
	socklen_t			cli_len;

	cli_len = sizeof(cli_addr);
	bzero(buffer, STREAM_SIZE + 1);
	newsockfd = accept(socfd, (struct sockaddr *)&cli_addr, &cli_len);
	while (1)
	{
		if (0 == process_stream(buffer, &newsockfd))
		{
			printf("shutting down server\n");
			break ;
		}
		// validate_url()
		send_to_internet(buffer);
		// send_to_internet();
		n = write(newsockfd, "$ : ", 4);
		if (n < 0)
			error("ERROR writing to socket");
	}
}

/*
 *	> establish connection port
 *	> wait for connections
 *	> on connection fork process
 */

int						main(int argc, char *argv[])
{
	int					sockfd;
	int					portno;
	struct sockaddr_in	serv_addr;

	if (argc < 2)
	{
		printf("ERROR: no port provided\n");
		exit(1);
	}

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0)
		error("ERROR: opening socket");
	bzero((char *)&serv_addr, sizeof(serv_addr));

	portno = atoi(argv[1]);

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(portno);

	if (bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
		error("ERROR: on binding");
	listen(sockfd, 5);
	wait_for_stream(sockfd);
	return (0);
}
