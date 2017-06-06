/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proxy_server.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mba <mba@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/17 15:17:05 by zsmith            #+#    #+#             */
/*   Updated: 2017/06/06 11:33:16 by mba              ###   ########.fr       */
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
#include <h3.h>				// request parsing

# define STREAM_SIZE 10000

struct          s_soc_info
{
    int         sockfd;
    char        buf[STREAM_SIZE];
    int         byte_count;
};

void        send_to_internet(char *buf, RequestHeader *header);
// void        send_to_internet();
void		error(char *msg);
char		*ft_strjoin(char const *s1, char const *s2);


#endif
