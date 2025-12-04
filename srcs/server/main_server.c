/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_server.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relaforg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 15:20:01 by relaforg          #+#    #+#             */
/*   Updated: 2025/12/04 14:00:21 by relaforg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <signal.h>
#include "libft.h"

#define SIZE_BYTES 4

typedef struct s_message
{
	unsigned int	size;
	char			*message;
}	t_message;

t_message	message;

void	signal_handler(int signal)
{
	static unsigned int	bit_count;
	static unsigned int	c;

	c = c << 1;
	if (signal == SIGUSR2)
		c = c | 1;
	bit_count++;
	message.message[23] = 'd';
	if (bit_count % 8 == 0)
	{
		if (message.size == 0 && bit_count == 8 * SIZE_BYTES)
		{
			message.size = c;
			message.message = ft_calloc(message.size, sizeof(char));
			if (!message.message)
				exit(1);
			c = 0;
		}
		else if (message.size)
		{
			if (!c)
			{
				ft_printf("%s\n", message.message);
				message.size = 0;
				bit_count = 0;
				free(message.message);
			}
			else
				message.message[bit_count / 8 - SIZE_BYTES - 1] = c;
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
	act.sa_handler = signal_handler;
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
