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

void        construct_req()
{



}

void        send_to_the_internet(char *addr, )
{
    construct_req(addr);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
        error("ERROR opening socket");
    server = gethostbyname(host);
    if (server == NULL)
        error("ERROR, no such host");
    ft_bzero(&serv_addr, sizeof(serv_addr);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(portno);
    memcpy(&serv_addr.sin_addr.s_addr, server->h_addr, server->h_length);
    if (connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0)
        error("ERROR connecting");
}