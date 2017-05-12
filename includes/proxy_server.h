/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proxy_server.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsmith <zsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/17 15:17:05 by zsmith            #+#    #+#             */
/*   Updated: 2017/05/11 19:31:30 by zsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROXY_SERVER_H
# define PROXY_SERVER_H

#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <ft_printf.h>

# define STREAM_SIZE 256

struct          s_soc_info
{
    int         sockfd;
    char        buf[2056];
    int         byte_count;
};

struct          s_url
{
    char        *url;
    char        *header;
};

void        send_to_internet(char *addr);

#endif
