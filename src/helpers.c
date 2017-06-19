/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mba <mba@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/01 16:37:27 by mba               #+#    #+#             */
/*   Updated: 2017/06/18 21:28:02 by mba              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <proxy_server.h>

void	error(char *msg)
{
	perror(msg);
	exit(1);
}

int		buffer_append(char **buf, char *data, int data_size)
{
	char	*temp = 0;
	int		buf_size;

	buf_size = strlen(*buf);
	temp = *buf;
	*buf = (char *)malloc(buf_size + data_size + 1);
	if (buf == 0)
		error("ERROR: error appending to buffer\n");
	(*buf)[buf_size + data_size] = 0;
	memmove(*buf, temp, buf_size);
	memmove(*buf + buf_size, data, data_size);
	free(temp);
	return (buf_size + data_size);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		len;
	int		i;
	char	*ret_str;

	if (!s1 || !s2)
		return (NULL);
	len = strlen(s1) + strlen(s2);
	ret_str = (char *)malloc(len + 1);
	if (ret_str == 0)
		return (NULL);
	i = 0;
	while (len >= 0 && *s1)
	{
		ret_str[i] = *s1;
		s1++;
		i++;
	}
	while (*s2)
	{
		ret_str[i] = *s2;
		s2++;
		i++;
	}
	ret_str[i] = '\0';
	return (ret_str);
}