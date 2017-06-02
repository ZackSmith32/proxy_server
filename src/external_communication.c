/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external_communication.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mba <mba@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/17 15:17:05 by zsmith            #+#    #+#             */
/*   Updated: 2017/06/02 00:41:14 by mba              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <proxy_server.h>

void        send_to_internet(char *addr)
{
    struct addrinfo     hints;
    struct addrinfo     *res;
    struct s_soc_info   sock_info;
    char                *header;

    printf("send_to_internet\n");
    bzero(&hints, sizeof(hints));
    res = (struct addrinfo *)malloc(sizeof(res));
    bzero(res, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    getaddrinfo(addr, "80", &hints, &res);
    printf("after get addr info\n");

	printf("ai_family = %d\n", res->ai_family);
	// printf("ai_socktype = %d\n", res->ai_socktype);
	// printf("ai_protocol = %d\n", res->ai_protocol);
	printf("test\n");

    sock_info.sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);

    printf("Connecting...\n");

    connect(sock_info.sockfd, res->ai_addr, res->ai_addrlen);
    printf("Connected!\n");
    header = strdup("GET /index.html HTTP/1.1\r\nHost: www.google.com\r\n\r\n");
    send(sock_info.sockfd, header, strlen(header), 0);
    sock_info.byte_count = recv(sock_info.sockfd, sock_info.buf, sizeof(sock_info.buf) - 1, 0);
    sock_info.buf[sock_info.byte_count] = '\0';
    printf("recv()'d %d bytes of data in sock_info.buf\n", sock_info.byte_count);
    printf("%s", sock_info.buf);
}
