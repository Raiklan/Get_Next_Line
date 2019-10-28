/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saich <saich@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 19:19:49 by saich             #+#    #+#             */
/*   Updated: 2019/10/28 17:36:15 by saich            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static ssize_t		pos_nextline(char *s)
{
	ssize_t	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

static int			extract(ssize_t r_size, char **line, char **cache, int index)
{
	char	*s;
	int		ret;

	(void)r_size;
	s = *cache;
	if (index >= 0)
	{
		*line = ft_substr(s, 0, index);
		*cache = ft_substr(s, index + 1, ft_strlen(s) - index - 1);
		ret = 1;
	}
	else
	{
		*line = ft_substr(s, 0, ft_strlen(s));
		*cache = ft_substr(s, 0, 0);
		ret = 0;
	}
	free(s);
	return (ret);
}

int					get_next_line(int fd, char **line)
{
	ssize_t		r_size;
	char		buff[BUFFER_SIZE + 1];
	static char	*cache;

	if (fd < 0 || !line)
		return (-1);
	while ((r_size = read(fd, buff, BUFFER_SIZE)) > 0)
	{
		buff[r_size] = '\0';
		cache = ft_strjoin(cache, buff);
		if (pos_nextline(cache) != -1)
			break ;
	}
	if (r_size < 0 && !(*line = 0))
	{
		if (cache)
			free(cache);
		return (-1);
	}
	if (r_size == 0 && (!cache || *cache == '\0') && (*line = ft_substr(buff, 0, 0)))
		return (0);
	return (extract(r_size, line, &cache, pos_nextline(cache)));
}
