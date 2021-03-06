/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proxy_server.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mba <mba@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/17 15:17:05 by zsmith            #+#    #+#             */
/*   Updated: 2017/06/18 22:03:18 by mba              ###   ########.fr       */
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
int		read_stream(char **buffer, int *newsockfd)
{
	int					data_size;
	int					buff_size;
	char				data[STREAM_SIZE + 1];

	
	bzero(data, STREAM_SIZE + 1);
	buff_size = 0;
	while (1) 
	{
		printf("read stream\n");
		data_size = read(*newsockfd, data, STREAM_SIZE);
		printf("request bytes = %d\n", data_size);
		if (data_size < 0)
			error("ERROR: reading from socket");
		buffer_append(buffer, data, data_size);
		printf("after buffer append\n");
		buff_size += data_size;
		if (data_size != STREAM_SIZE)
			return (buff_size);
	}
	return (-1);
}

void	extract_req(char *buf, RequestHeader *header) 
{

    
    h3_request_header_parse(header, buf, strlen(buf));

    printf("HEADER\n");
    printf("===========================\n");
    printf("%s", buf);
    printf("\n---------------------------\n");
    printf("Method: %.*s\n", header->RequestMethodLen, header->RequestMethod);
    printf("Request-URI: %.*s\n", header->RequestURILen, header->RequestURI);
    printf("HTTP-Version: %.*s\n", header->HTTPVersionLen, header->HTTPVersion);
    printf("header size = %d\n", header->HeaderSize);
    printf("FieldName[0]: %.*s\n", (header->Fields[0]).FieldNameLen, (header->Fields[0]).FieldName);
    printf("===========================\n");

    // h3_request_header_free(header);

	
}


/*
 *	> loop to continue listening

	Questions:
		> what do we use cli_addr for?

 */

void	listen_stream(int socfd)
{
	char				*buffer;
	int					newsockfd;
	struct sockaddr_in	cli_addr;
	socklen_t			cli_len;
	RequestHeader 		*header;
	struct s_soc_info   soc_info;
	int					buffer_len;
	// int					n;

	buffer = (char *)malloc(1);
	buffer[0] = 0;
	cli_len = sizeof(cli_addr);
	newsockfd = accept(socfd, (struct sockaddr *)&cli_addr, &cli_len);
	if (newsockfd < 0)
		error("ERROR: on accept");
	header = h3_request_header_new();
	// bzero(buffer, STREAM_SIZE + 1);
	while (1) 
	{
		printf("***************************\n");
		buffer_len = read_stream(&buffer, &newsockfd);
		printf("read: %s\n", buffer);

		// todo : add validation to request
		extract_req(buffer, header);
		/*
		 *	header now contains all references to the buffer
		 */
		connect_to_host(header, buffer_len, &soc_info, newsockfd);
		// printf("%s\n", soc_info.buf);
		// printf("res_buf = %s\n", res_buf);
		// printf("n = %d\n", n);
		printf("***************************\n");		
		
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
	printf("WTF\n");
	listen(sockfd, 5);
	listen_stream(sockfd);
	return (0);
}























