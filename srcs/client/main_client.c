/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_client.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relaforg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 15:29:32 by relaforg          #+#    #+#             */
/*   Updated: 2025/12/03 17:30:09 by relaforg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "libft.h"

void	send_char(char c, int pid)
{
	int	i;

	i = 0;
	while (c || i < 8)
	{
		if (c % 2)
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		i++;
		c /= 2;
		usleep(100);
	}
}

int	main(int argc, char **argv)
{
	int	pid;

	if (argc < 3)
		return (0);
	pid = ft_atoi(argv[1]);
	while (*argv[2])
	{
		send_char(*argv[2], pid);
		argv[2]++;
		usleep(100);
	}
	// int	i = 0;
	// while (i < 8)
	// {
	// 	kill(pid, SIGUSR1);
	// 	i++;
	// 	usleep(100);
	// }
	return (0);
}
