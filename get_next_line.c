/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saich <saich@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 17:43:09 by saich             #+#    #+#             */
/*   Updated: 2019/10/28 18:07:14 by saich            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char		*ft_strnew(void)
{
	char *ret;

	if (!(ret = malloc(sizeof(char))))
		return (0);
	ret[0] = '\0';
	return (ret);
}

static ssize_t	pos_nextline(char *s)
{
	ssize_t i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

static int		free_cache(char **cache, int ret)
{
	if (*cache)
	{
		free(*cache);
		*cache = 0;
	}
	return (ret);
}
static int		extract(char **line, char *cache, int index)
{
	char	*tmp;
	int		ret;

	if (index >= 0)
	{
		if (!(*line = ft_substr(*cache, 0, index)))
			return (free_cache(cache, -1));
		if (!(tmp = ft_substr(*cache, index + 1, ft_strlen(*cache) - index - 1)))
			return (free_cache(cache, -1));
		ret = 1;
	}
	else
	{
		if (!(*line = ft_substr(*cache, 0, ft_strlen(*cache))))
			return (free_cache(cache, -1));
		tmp = 0;
		ret = 0;
	}
	free_cache(cache, 0);
	*cache = tmp;
	return (ret);
}
int				get_next_line(int fd, char **line)
{
	ssize_t		read_size;
	char		buff[BUFFER_SIZE + 1];
	static char	*cache;
	char		*tmp;

	if (fd < 0 || !line)
		return (-1);
	while ((read_size = read(fd, buff, BUFFER_SIZE) > 0))
	{
		buff[read_size] = '\0';
		if (!(tmp = ft_strjoin(cache, buff, read_size)))
			return (free_cache(&cache, -1));
		free_cache(&cache, 0);
		cache = tmp;
		if (pos_nextline(cache) != -1)
			break ;
	}
	if (read_size < 0)
		return (free_cache(&cache, -1));
	if (read_size == 0 && (!cache || *cache == '\0') && (*line = ft_strnew()))
		return (free_cache(&cache, 0));
	return (extract(line, &cache, pos_nextline(cache)));
}
