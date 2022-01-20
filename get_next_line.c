/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bibrahim <bibrahim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 16:42:50 by bibrahim          #+#    #+#             */
/*   Updated: 2022/01/07 16:49:34 by bibrahim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_read(char *s, int fd)
{
	char	*buf;
	int		n;

	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	n = 1;
	while (ft_strchr(s, '\n') == NULL && n != 0)
	{
		n = read(fd, buf, BUFFER_SIZE);
		if (n == -1)
		{
			free(buf);
			return (NULL);
		}
		buf[n] = '\0';
		s = ft_strjoin(s, buf);
	}
	free(buf);
	return (s);
}

char	*change_the_static(char *s)
{
	char	*news;
	size_t	i;
	size_t	l;

	l = 0;
	while (s[l] != '\n' && s[l] != '\0')
		l++;
	if (ft_strlen(s) == l)
	{
		free(s);
		return (NULL);
	}
	news = (char *)malloc((ft_strlen(s) - l + 1) * sizeof(char));
	if (news == NULL)
		return (NULL);
	i = 0;
	while (s[l++])
	{
		news[i] = s[l];
		i++;
	}
	news[i] = '\0';
	free(s);
	return (news);
}

char	*get_line(char *res)
{
	char	*line;
	size_t	l;
	size_t	i;

	l = 0;
	if (res[0] == '\0')
		return (NULL);
	while (res[l] != '\n' && res[l] != '\0')
		l++;
	if (res[l] == '\n')
		l++;
	line = (char *)malloc(sizeof(char) * l + 1);
	if (line == NULL)
		return (NULL);
	i = 0;
	while (i < l)
	{
		line[i] = res[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*s;
	char		*buf;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	s = ft_read(s, fd);
	if (s == NULL)
		return (NULL);
	buf = get_line(s);
	s = change_the_static(s);
	return (buf);
}
