/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mba <mba@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/01 16:37:27 by mba               #+#    #+#             */
/*   Updated: 2017/06/02 00:10:59 by mba              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <proxy_server.h>

void	error(char *msg)
{
	perror(msg);
	exit(1);
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