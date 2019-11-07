/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saich <saich@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 15:00:33 by saich             #+#    #+#             */
/*   Updated: 2019/11/07 18:06:40 by saich            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char			*ft_strnew(void)
{
	char *ret;

	if (!(ret = (char *)malloc(sizeof(char) * 1)))
		return (0);
	ret[0] = '\0';
	return (ret);
}

int				del_cache(t_cache **begin, int fd)
{
	t_cache	*tmp;
	t_cache	*now;
	t_cache	*next;

	tmp = *begin;
	now = tmp;
	while (now)
	{
		next = now->next;
		if (now->fd == fd)
		{
			if (now->content)
				free(now->content);
			if (tmp != now)
				tmp->next = next;
			else if (tmp == now)
				*begin = next;
			free(now);
			break ;
		}
		tmp = now;
		now = now->next;
	}
	return (1);
}

static t_cache	*new_cache(int fd)
{
	t_cache	*cur;

	if (!(cur = (t_cache*)malloc(sizeof(t_cache))))
		return (0);
	cur->fd = fd;
	cur->content = 0;
	cur->next = 0;
	return (cur);
}

t_cache			*find_cache_by_fd(t_cache **begin, int fd)
{
	t_cache	*cur;
	t_cache *tmp;

	if (*begin == 0)
	{
		*begin = new_cache(fd);
		return (*begin);
	}
	cur = *begin;
	tmp = 0;
	while (cur)
	{
		if (cur->fd == fd)
			return (cur);
		tmp = cur;
		cur = cur->next;
	}
	tmp->next = new_cache(fd);
	return (tmp->next);
}

int				get_next_line(int fd, char **line)
{
	ssize_t			r_size;
	char			buff[BUFFER_SIZE + 1];
	static t_cache	*begin;
	t_cache			*cur;

	if (fd < 0 || !line)
		return (-1);
	cur = find_cache_by_fd(&begin, fd);
	while ((r_size = read(fd, buff, BUFFER_SIZE)) > 0)
	{
		buff[r_size] = '\0';
		cur->content = ft_strjoin(cur->content, buff);
		if (pos_nextline(cur->content) != -1)
			break ;
	}
	if (r_size < 0 && !(*line = 0))
		return (-1);
	if (r_size == 0 && (!(cur->content) || *(cur->content) == '\0')
		&& (*line = ft_strnew()) && del_cache(&begin, fd))
		return (0);
	return (extract(line, &begin, pos_nextline(cur->content), fd));
}
