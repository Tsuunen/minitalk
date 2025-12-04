/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_server.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relaforg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 15:20:01 by relaforg          #+#    #+#             */
/*   Updated: 2025/12/04 14:46:07 by relaforg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <signal.h>
#include "libft.h"

typedef struct s_message
{
	unsigned int	size;
	char			*message;
}	t_message;

t_message	message;

void	signal_handler(int signal, siginfo_t *info, void *context)
{
	static unsigned int	bit_count;
	static unsigned int	c;
	(void) context;

	c = c << 1;
	if (signal == SIGUSR2)
		c = c | 1;
	bit_count++;
	if (bit_count % 32 == 0)
	{
		if (message.size == 0)
		{
			message.size = c;
			message.message = ft_calloc(message.size, sizeof(char));
			if (!message.message)
			{
				kill(info->si_pid, SIGUSR2);
				exit(1);
			}
			c = 0;
		}
		else
		{
			if (!c)
			{
				ft_printf("%s\n", message.message);
				message.size = 0;
				bit_count = 0;
				free(message.message);
				message.message = NULL;
				kill(info->si_pid, SIGUSR1);
			}
			else
				message.message[bit_count / 32 - 2] = c;
			c = 0;
		}
	}
}

void	clean_exit(int signal)
{
	if (signal == SIGSEGV)
		ft_printf("Segmentation Fault: you noob\n");
	if (message.message)
		free(message.message);
	exit(0);
}

int	main(void)
{
	pid_t	pid;
	struct sigaction	act;
	struct sigaction	act_quit;

	message.message = NULL;
	message.size = 0;
	ft_bzero(&act, sizeof(act));
	act.sa_flags = SA_SIGINFO;
	act.sa_sigaction = signal_handler;
	ft_bzero(&act_quit, sizeof(act));
	act_quit.sa_handler = clean_exit;
	sigaction(SIGUSR1, &act, NULL);
	sigaction(SIGUSR2, &act, NULL);
	sigaction(SIGINT, &act_quit, NULL);
	sigaction(SIGSEGV, &act_quit, NULL);
	pid = getpid();
	ft_printf("%d\n", pid);
	while (1);
	return (0);
}
