/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_client.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relaforg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 15:29:32 by relaforg          #+#    #+#             */
/*   Updated: 2025/12/04 14:43:29 by relaforg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "libft.h"

void	send_char(unsigned int c, int pid, int i)
{
	if (i == 0)
		return ;
	send_char(c / 2, pid, i - 1);
	if (c % 2)
		kill(pid, SIGUSR2);
	else
		kill(pid, SIGUSR1);
	usleep(100);
}

void	catch_response(int signal)
{
	ft_printf("Server reponded : ");
	if (signal == SIGUSR1)
	{
		ft_printf("Successfull\n");
		exit(0);
	}
	else
	{
		ft_printf("Failed\n");
		exit(1);
	}
}

int	main(int argc, char **argv)
{
	int	pid;
	struct sigaction	act;

	ft_bzero(&act, sizeof(act));
	act.sa_handler = catch_response;
	sigaction(SIGUSR1, &act, NULL);
	sigaction(SIGUSR2, &act, NULL);
	if (argc < 3)
		return (0);
	pid = ft_atoi(argv[1]);
	send_char(ft_strlen(argv[2]) + 1, pid, 32);
	while (*argv[2])
	{
		send_char(*argv[2], pid, 32);
		argv[2]++;
		usleep(100);
	}
	send_char(0, pid, 32);
	while(1);
	return (0);
}
