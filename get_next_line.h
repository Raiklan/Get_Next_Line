/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saich <saich@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 17:34:34 by saich             #+#    #+#             */
/*   Updated: 2019/10/29 17:34:37 by saich            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

int				get_next_line(int fd, char **line);
ssize_t			ft_strlen(const char *s);
char			*ft_strjoin(char *s1, char *s2, ssize_t read_size);
char			*ft_substr(char const *s, unsigned int start, ssize_t len);

#endif
