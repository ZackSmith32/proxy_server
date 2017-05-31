/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proxy_server.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mba <mba@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/17 15:17:05 by zsmith            #+#    #+#             */
/*   Updated: 2017/05/31 15:45:37 by mba              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROXY_SERVER_H
# define PROXY_SERVER_H

#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>			// printf
#include <stdlib.h>			// bzero, atoi
#include <unistd.h>			// read

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
