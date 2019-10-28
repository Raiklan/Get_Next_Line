/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saich <saich@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 19:22:52 by saich             #+#    #+#             */
/*   Updated: 2019/10/24 20:52:48 by saich            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include "get_next_line.h"

int main(int ac, char** argv)
{
 	int fd = open(argv[1], O_RDONLY);
 	int	i = 0;
 	int	res = 0;
 	char *str = 0;
	(void)ac;
	printf("fd2 : %d\n", fd);
	while ((res = get_next_line(fd, &str)) > 0)
	{
		printf("ligne %d : {%s}\n", ++i, str);
		free(str);
	}
	close(fd);
	printf("str : {%s}\n", str);
 	return (0);
 }
