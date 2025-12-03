/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_server.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relaforg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 15:20:01 by relaforg          #+#    #+#             */
/*   Updated: 2025/12/03 17:14:13 by relaforg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <signal.h>
#include "libft.h"

void	test(int signal)
{
	if (signal == SIGUSR1)
		ft_printf("0\n");
	else if (signal == SIGUSR2)
		ft_printf("1\n");
}

int	main(void)
{
	pid_t	pid;
	struct sigaction act;

	ft_bzero(&act, sizeof(act));
	act.sa_handler = test;
	sigaction(SIGUSR1, &act, NULL);
	sigaction(SIGUSR2, &act, NULL);
	pid = getpid();
	ft_printf("%d\n", pid);
	while (1);
	return (0);
}
