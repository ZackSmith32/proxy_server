/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external_communication.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mba <mba@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/17 15:17:05 by zsmith            #+#    #+#             */
/*   Updated: 2017/06/06 11:59:12 by mba              ###   ########.fr       */
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
	len -= 1;
	while (len >= i) {
		uri[len] = 0;
		len--;
	}
	printf("len = %d\n", len);


}

char *generate_out_header(RequestHeader *h) {
	// char	*request_line;
	char	*host_line;
	int		host_len = 0;
	char	*header_field;
	unsigned int		i = 0;

	printf("generate_ot_header headerSize = %d\n", h->HeaderSize);
	/*
	 *	minus 1 because the header size includes the get request, but the "Fields"
	 *		property does not
	 */
	while (i < h->HeaderSize - 1) {

		header_field = (char *)h->Fields[i].FieldName;
		printf("i = %d, len = %d, header_field = %.*s\n",i,  h->Fields[i].FieldNameLen, h->Fields[i].FieldNameLen, header_field);
		if (strncmp(header_field, "Host:", 5) == 0) {
			printf("********************************************************************\n");
			printf("value = %.*s, len = %d\n", h->Fields[i].ValueLen, h->Fields[i].Value, h->Fields[i].ValueLen);
			host_len = h->Fields[i].FieldNameLen + h->Fields[i].ValueLen + 2 + 1;
			host_line = (char *)malloc(host_len);
			bzero(host_line, host_len);
			strncpy(host_line, h->Fields[i].FieldName, host_len - 1);
		}
		i++;
	}
	printf("out of while\n");
	printf("\nlen = %d, headerField host = %s<\n\n", host_len, host_line);
	return (host_line);
}

void        send_to_internet(char *buf, RequestHeader *header)
{
	struct addrinfo     hints;
	struct addrinfo     *res;
	struct s_soc_info   sock_info;
	char                *req_uri;
	// char             *header;

	buf[0] = 0;
	header->HeaderSize++;

	bzero(&hints, sizeof(struct addrinfo));
	(hints).ai_family = AF_UNSPEC;
	(hints).ai_socktype = SOCK_STREAM;

	req_uri = (char *)malloc(header->RequestURILen + 1);
	bzero(req_uri, header->RequestURILen + 1);
	strncpy(req_uri, header->RequestURI, header->RequestURILen);
	trim_uri(req_uri, header->RequestURILen);
	printf("trimmed = %s\n", req_uri);
  
  	printf("after trimmed\n");
	int rv;
	if ((rv = getaddrinfo(req_uri, "http", &hints, &res)) != 0) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
		exit(1);
	}	
	printf("after get addr info\n");


	sock_info.sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
	printf("Connecting...\n");
	connect(sock_info.sockfd, res->ai_addr, res->ai_addrlen);
	printf("Connected!\n");


	char *req = strdup("GET http://www.pittsburghpostgazette.com/ HTTP/1.1\r\nHost: www.pittsburghpostgazette.com\r\n\r\n");
	// printf("after strdup\n");
	char *out_header;
	// printf("headerSize = %d\n", header->HeaderSize);
	out_header = generate_out_header(header);
	send(sock_info.sockfd, req, strlen(req), 0);
	printf("after send\n");

	sock_info.byte_count = recv(sock_info.sockfd, sock_info.buf, sizeof(sock_info.buf) - 1, 0);
	sock_info.buf[sock_info.byte_count] = '\0';


	printf("recv()'d %d bytes of data in sock_info.buf\n", sock_info.byte_count);
	printf("%s", sock_info.buf);

}































