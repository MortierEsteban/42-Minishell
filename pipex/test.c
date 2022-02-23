/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emortier <emortier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 09:48:48 by emortier          #+#    #+#             */
/*   Updated: 2022/02/21 16:03:52 by emortier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"./incl/pipex.h"

int	main(int ac, char **av)
{
	int	fd;
	pid_t	forked;
	char	*str;
	int		pipes[2];

	(void) ac;
	(void) av;
	str = malloc (125);
	pipe(pipes);
	fd = open("test.txt", O_RDWR);
	forked = fork();
	if (forked == -1)
	{
		printf("cça fait nimp");
		return (0);
	}
	if (forked == 0)
	{
		close (pipes[0]);
		write (pipes[1], "Here goes nothing", 17);
	}
	else
	{
		close(pipes[1]);
		wait(NULL);
		dup2(fd, 1);
		printf("read = %zd\n", read(pipes[0], str, 18));
		close(pipes[0]);
	}
	printf("%s\n", str);
	return (0);
}
