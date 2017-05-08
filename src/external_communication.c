/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external_communication.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsmith <zsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/17 15:17:05 by zsmith            #+#    #+#             */
/*   Updated: 2017/02/17 15:50:04 by zsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <proxy_server.h>

void        construct_req(struct s_url temp, char *addr)
{
    char    *str;
    char    *temp;

    temp.url = addr;
    str = ft_strdup("GET /index.html HTTP/1.1\r\nHost: ");
    temp = ft_strjoin(str, addr);
    free(str);
    str = ft_strjoin(temp, "\r\n\r\n");

}

void        send_to_the_internet(char *addr)
{
    struct addrinfo     hints;
    struct addrinfo     *res;
    struct s_soc_info   sock_info;
    char                *header;
    struct s_url        *url_struct;

    contruct_req(buf, url_struct);
    ft_bzero(&hints, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    getaddrinfo("www.google.com", "80", &hints, &res);
    sock_info.sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    printf("Connecting...\n");
    connect(sock_info.sockfd, res->ai_addr, res->ai_addrlen);
    printf("Connected!\n");
    header = ft_strdup("GET /index.html HTTP/1.1\r\nHost: www.qst0.com\r\n\r\n");
    send(sock_info.sockfd, header, ft_strlen(header), 0);
    sock_info.byte_count = recv(sock_info.sockfd, sock_info.buf, sizeof(sock_info.buf) - 1, 0);
    sock_info.buf[sock_info.byte_count] = '\0';
    printf("recv()'d %d bytes of data in sock_info.buf\n", sock_info.byte_count);
    printf("%s", sock_info.buf);
}




