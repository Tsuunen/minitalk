/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relaforg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 15:20:01 by relaforg          #+#    #+#             */
/*   Updated: 2025/12/03 15:29:14 by relaforg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <signal.h>
#include "libft.h"

int	main(void)
{
	pid_t	pid;
	sigset_t	sigset;

	if (sigaddset(&sigset, SIGUSR1) == -1)
		return (1);
	if (sigaddset(&sigset, SIGUSR2) == -1)
	{
		sigemptyset(&sigset);
		return (1);
	}
	pid = getpid();
	ft_printf("%d\n", pid);
	while (1);
	sigemptyset(&sigset);
	return (0);
}
