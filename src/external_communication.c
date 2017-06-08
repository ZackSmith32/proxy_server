/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external_communication.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mba <mba@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/17 15:17:05 by zsmith            #+#    #+#             */
/*   Updated: 2017/06/08 11:34:05 by mba              ###   ########.fr       */
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
	char	*req_line;
	int		req_len = 0;
	char	*header_field;
	unsigned int		i = 0;

	/*
	 *	minus 1 because the header size includes the get request, but the "Fields"
	 *		property does not
	 */
	while (i < h->HeaderSize - 1) {

		header_field = (char *)h->Fields[i].FieldName;
		printf("i = %d, len = %d, header_field = %.*s\n",i,  h->Fields[i].FieldNameLen, h->Fields[i].FieldNameLen, header_field);
		if (strncmp(header_field, "Host:", 5) == 0) {
			break ;
		}
		i++;
	}
	printf("out of while\n");
	req_len = h->Fields[i + 1].FieldName - h->RequestLineStart + 1;
	printf("req_len = %d\n", req_len);
	req_line = (char *)malloc(req_len);
	bzero(req_line, req_len);
	strncpy(req_line, h->RequestLineStart, req_len - 1);
	char *rs;
	rs = ft_strjoin(req_line, "\r\n");
	free(req_line);

	return (rs);
}

void		send_req(RequestHeader *header, struct s_soc_info *sock_info) {
	char		*out_header;
	char		response[STREAM_SIZE];
	int			res_size = 0;
	char		*temp;

	out_header = generate_out_header(header);
	// send(sock_info->sockfd, out_header, strlen(out_header), 0);
	send(sock_info->sockfd, out_header, strlen(out_header), 0);
	printf("request sent..\n");

	while ((res_size = recv(sock_info->sockfd,
				response, STREAM_SIZE - 1, 0)))
	{
		printf("res_size = %d\n", res_size);
		sock_info->byte_count += res_size;
		temp = sock_info->buf;
		sock_info->buf = ft_strjoin(sock_info->buf, response);
		free(temp);
		if (res_size != STREAM_SIZE - 1)
			break ;
	}

	printf("recv()'d %d bytes of data in sock_info.buf\n", sock_info->byte_count);
}

char		*connect_to_host(RequestHeader *header)
{
	struct addrinfo     hints;
	struct addrinfo     *res;
	struct s_soc_info   sock_info;
	char                *req_uri;
	int 				rv;

	bzero(&hints, sizeof(struct addrinfo));
	(hints).ai_family = AF_UNSPEC;
	(hints).ai_socktype = SOCK_STREAM;

	req_uri = (char *)malloc(header->RequestURILen + 1);
	bzero(req_uri, header->RequestURILen + 1);
	strncpy(req_uri, header->RequestURI, header->RequestURILen);
	trim_uri(req_uri, header->RequestURILen);
	printf("trimmed = %s\n", req_uri);
  
	// if ((rv = getaddrinfo(req_uri, "http", &hints, &res)) != 0) {
	if ((rv = getaddrinfo("www.qst0.com", "http", &hints, &res)) != 0) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
		exit(1);
	}	

	bzero(&sock_info, sizeof(sock_info));
	sock_info.buf = (char *)malloc(1);
	sock_info.buf[0] = 0;
	sock_info.sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
	printf("Connecting...\n");
	connect(sock_info.sockfd, res->ai_addr, res->ai_addrlen);
	printf("Connected!\n");
	send_req(header, &sock_info);
	
	return (sock_info.buf);
}































