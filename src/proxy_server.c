/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proxy_server.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mba <mba@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/17 15:17:05 by zsmith            #+#    #+#             */
/*   Updated: 2017/06/02 00:57:25 by mba              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <proxy_server.h>



/*
 *	Receive data stream from client
 *		> remove client specific information
 *		> construct outgoing request
 *	> reading from sockfd
 *		> telnet
 *			>read returns whenever it encounters a nl character
 *			> it will return the number of bits read, up to max read size
 *		> from browser
 *			> read stops at the end of a request...
 *			> if you tell read to read on a stream that it finished on,
 *				read hangs there.
 */
int		read_stream(char *buffer, int *newsockfd)
{
	int					n;
	int					index;

	if (newsockfd < 0)
		error("ERROR: on accept");
	bzero(buffer, STREAM_SIZE + 1);
	index = 0;
	while (1) 
	{
		n = read(*newsockfd, &(buffer[index]), STREAM_SIZE);
		index += n;
		if (n == 0 || n != STREAM_SIZE)
			return (0);
		else if (n < 0)
			error("ERROR: reading from socket");
		printf("~ %s\n", buffer);
	}
	return (1);
}

void	extract_req(char *buf) 
{
	int		i;

	i = 0;
	while (buf[i] != '\n')
	{
		if (buf[i] == '\0')
			error("ERROR: bad request");
		i++;
	}
	while (buf[i] != '\0')
	{
		buf[i] = '\0';
		i++;
	}
}


/*
 *	> loop to continue listening

	Questions:
		> what do we use cli_addr for?

 */

void	listen_stream(int socfd)
{

	char				buffer[STREAM_SIZE + 1];
	int					newsockfd;
	struct sockaddr_in	cli_addr;
	socklen_t			cli_len;

	cli_len = sizeof(cli_addr);
	bzero(buffer, STREAM_SIZE + 1);
	newsockfd = accept(socfd, (struct sockaddr *)&cli_addr, &cli_len);
	
	read_stream(buffer, &newsockfd);
	// todo : add validation to request
	extract_req(buffer);
	printf("new buf = %s\n", buffer);

	send_to_internet(buffer);
	// n = write(newsockfd, "$ : ", 4);
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
	listen_stream(sockfd);
	return (0);
}
