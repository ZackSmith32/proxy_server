/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external_communication.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mba <mba@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/17 15:17:05 by zsmith            #+#    #+#             */
/*   Updated: 2017/06/05 17:44:28 by mba              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <proxy_server.h>

void		trim_uri(char *uri, int len) {
	char		*pattern = "http://";
	int			i = 0;

	printf("len = %d\n", len);
	if (len < 7) {
		printf("early return len = %d\n", len);
		return ;
	}
	while (i + 7 < len) {
		if (i < 7 && uri[i] != pattern[i])
			error("ERROR: path does not include 'http://'");
		uri[i] = uri[i + 7];
		i++;
	}
	while (len >= i) {
		uri[len] = 0;
		len--;
	}


}
void        send_to_internet(char *buf, RequestHeader *header)
{
	struct addrinfo     *hints;
	struct addrinfo     *res;
	struct s_soc_info   sock_info;
	char                *req_uri;
	// char             *header;


	buf[0] = 0;
	printf("send_to_internet\n");

	hints = (struct addrinfo *)malloc(sizeof(struct addrinfo));
	res = (struct addrinfo *)malloc(sizeof(struct addrinfo));
	bzero(hints, sizeof(struct addrinfo));
	bzero(res, sizeof(struct addrinfo));

	(*hints).ai_family = AF_UNSPEC;
	(*hints).ai_socktype = SOCK_STREAM;
	req_uri = (char *)malloc(header->RequestURILen + 1);
	bzero(req_uri, header->RequestURILen + 1);
	strncpy(req_uri, header->RequestURI, header->RequestURILen);
	trim_uri(req_uri, header->RequestURILen);
	printf("trimmed = %s\n", req_uri);
  
  	printf("after trimmed\n");
	int rv;
	if ((rv = getaddrinfo(req_uri, "http", hints, &res)) != 0) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
		exit(1);
	}	
	printf("after get addr info\n");


	sock_info.sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);

	printf("Connecting...\n");

	connect(sock_info.sockfd, res->ai_addr, res->ai_addrlen);
	printf("Connected!\n");
	// // header = strdup("GET http://www.pittsburghpostgazette.com/ HTTP/1.1\r\nHost: www.pittsburghpostgazette.com\r\n\r\n");
	send(sock_info.sockfd, "GET http://www.pittsburghpostgazette.com/ HTTP/1.1\r\n\r\n", 58, 0);
	printf("after send\n");
	sock_info.byte_count = recv(sock_info.sockfd, sock_info.buf, sizeof(sock_info.buf) - 1, 0);

	sock_info.buf[sock_info.byte_count] = '\0';
	printf("recv()'d %d bytes of data in sock_info.buf\n", sock_info.byte_count);
	printf("%s", sock_info.buf);
}































