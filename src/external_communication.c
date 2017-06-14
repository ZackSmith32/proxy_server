/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external_communication.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mba <mba@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/17 15:17:05 by zsmith            #+#    #+#             */
/*   Updated: 2017/06/12 15:58:43 by mba              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <proxy_server.h>

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
		if (strncmp(header_field, "Host:", 5) == 0) {
			break ;
		}
		i++;
	}
	req_len = h->Fields[i + 1].FieldName - h->RequestLineStart + 1;
	// printf("req_len = %d\n", req_len);
	req_line = (char *)malloc(req_len);
	bzero(req_line, req_len);
	strncpy(req_line, h->RequestLineStart, req_len - 1);
	char *rs;
	rs = ft_strjoin(req_line, "\r\n");
	free(req_line);

	return (rs);
}

void		send_req(RequestHeader *header, struct s_soc_info *sock_info, int header_size) {
	// char		*out_header;
	char		response[STREAM_SIZE + 1];
	int			res_size = 0;
	char		*temp;

	// out_header = generate_out_header(header);
	// send(sock_info->sockfd, out_header, strlen(out_header), 0);
	// printf("*********************************\n");
	// printf("sending:\n");
	// printf("%*s", header->HeaderSize, header->RequestLineStart);
	// printf("*********************************\n");
	send(sock_info->sockfd, header->RequestLineStart, header_size, 0);
	printf("request sent..\n");
	bzero(response, STREAM_SIZE + 1);
	while ((res_size = recv(sock_info->sockfd,
				response, STREAM_SIZE, 0)))
	{
		printf("res_size = %d\n", res_size);
		temp = sock_info->buf;
		sock_info->byte_count += res_size;
		sock_info->buf = ft_strjoin(sock_info->buf, response);
		free(temp);
		if (res_size != STREAM_SIZE)
			break ;
		else
			bzero(response, STREAM_SIZE + 1);
	
	}
	printf("recv()'d %d bytes of data in sock_info.buf\n", (int)sock_info->byte_count);
}

void	connect_to_host(RequestHeader *header, int header_size, struct s_soc_info *soc_info)
{
	struct addrinfo     hints;
	struct addrinfo     *res;
	
	int 				rv;

	bzero(&hints, sizeof(struct addrinfo));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	printf("hints\n");
  	char *host;
  	host = (char *)malloc(header->Fields[0].ValueLen + 1);
  	bzero(host, header->Fields[0].ValueLen + 1);
  	strncpy(host, header->Fields[0].Value, header->Fields[0].ValueLen);
  	printf("host = %s\n", host);
	if ((rv = getaddrinfo(host, "http", &hints, &res)) != 0) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
		exit(1);
	}	
	bzero(soc_info, sizeof(soc_info));
	soc_info->buf = (char *)malloc(1);
	soc_info->buf[0] = 0;
	soc_info->byte_count = 0;
	printf("res \n");
	soc_info->sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
	printf("Connecting...\n");
	connect(soc_info->sockfd, res->ai_addr, res->ai_addrlen);
	printf("Connected!\n");
	header_size++;
	send_req(header, soc_info, header_size);
	
}




























