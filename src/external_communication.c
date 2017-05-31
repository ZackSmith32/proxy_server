/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external_communication.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mba <mba@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/17 15:17:05 by zsmith            #+#    #+#             */
/*   Updated: 2017/05/31 15:58:04 by mba              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <proxy_server.h>


static void        construct_req(struct s_url *info, char *addr)
{
    char    *str;
    // char    *temp;

    printf("%s\n", addr);
    info->url = strdup(addr);
    printf("0\n");
    str = strdup("GET /index.html HTTP/1.1\r\nHost: ");
    printf("1\n");
    // need to find a substitute for strjoin
    // temp = strjoin(str, addr);
    printf("2\n");
    free(str);
    // str = strjoin(temp, "\r\n\r\n");
    printf("3\n");
    info->header = str;
}

void        send_to_internet(char *addr)
{
    struct addrinfo     hints;
    struct addrinfo     *res;
    struct s_soc_info   sock_info;
    char                *header;
    struct s_url        url_struct;

    printf("send_to_internet\n");
    construct_req(&url_struct, addr);
    bzero(&hints, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

	getaddrinfo(addr, "80", &hints, &res);

	printf("addr: %s\n", addr);
	// printf("ai_family = %d\n", res->ai_family);
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
