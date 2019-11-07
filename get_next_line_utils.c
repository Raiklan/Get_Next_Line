/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saich <saich@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 17:46:02 by saich             #+#    #+#             */
/*   Updated: 2019/11/07 18:07:21 by saich            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

ssize_t		pos_nextline(char *str)
{
	ssize_t	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

int			extract(char **line, t_cache **begin, int index, int fd)
{
	char	*str;
	int		ret;
	t_cache	*cur;

	cur = find_cache_by_fd(begin, fd);
	str = cur->content;
	if (index >= 0)
	{
		*line = ft_substr(str, 0, index);
		cur->content = ft_substr(str, index + 1, ft_strlen(str) - index - 1);
		ret = 1;
		free(str);
	}
	else
	{
		*line = ft_substr(str, 0, ft_strlen(str));
		del_cache(begin, fd);
		ret = 0;
	}
	return (ret);
}

ssize_t		ft_strlen(const char *str)
{
	ssize_t	len;

	if (!str)
		return (0);
	len = 0;
	while (str[len] != '\0')
		len++;
	return (len);
}

char		*ft_substr(char const *str, unsigned int start, ssize_t len)
{
	char	*ptr;
	char	*ret;
	char	*cpy_ret;

	if (!str || !(ret = (char*)malloc(sizeof(char) * (len + 1))))
		return (0);
	if (start >= ft_strlen(str))
		ret[0] = '\0';
	else
	{
		ptr = (char*)str + start;
		cpy_ret = ret;
		while (*ptr != '\0' && len-- > 0)
			*cpy_ret++ = *ptr++;
		*cpy_ret = '\0';
	}
	return (ret);
}

char		*ft_strjoin(char *s1, char *s2)
{
	int		len;
	char	*res;
	ssize_t	i;

	len = ft_strlen(s1) + ft_strlen(s2);
	if (!(res = (char*)malloc(sizeof(char) * (len + 1))))
		return (0);
	i = 0;
	while (s1 && s1[i] != '\0')
	{
		res[i] = s1[i];
		i++;
	}
	if (s1)
		free(s1);
	while (s2 && *s2 != '\0')
		res[i++] = *s2++;
	res[i] = '\0';
	return (res);
}
