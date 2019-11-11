/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saich <saich@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 15:12:10 by saich             #+#    #+#             */
/*   Updated: 2019/11/08 21:55:02 by saich            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

typedef struct		s_cache
{
	int				fd;
	char			*content;
	struct s_cache	*next;
}					t_cache;

ssize_t				pos_nextline(char *str);
int					extract(char **line, t_cache **begin, int index, int fd);
ssize_t				ft_strlen(const char *str);
char				*ft_substr(char const *str, unsigned int start,
					ssize_t len);
char				*ft_strjoin(char *s1, char *s2);
int					del_cache(t_cache **begin, int fd);
char				*ft_strnew(void);
t_cache				*find_cache_by_fd(t_cache **begin, int fd);
int					get_next_line(int fd, char **line);

#endif
