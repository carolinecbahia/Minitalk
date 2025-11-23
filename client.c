/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccavalca <ccavalca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 00:04:21 by ccavalca          #+#    #+#             */
/*   Updated: 2025/11/23 14:10:15 by ccavalca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

volatile sig_atomic_t	g_ack_received;

static void	ack_handler(int signal)
{
	(void)signal;
	g_ack_received = 1;
}

void	send_byte_and_wait(pid_t server_pid, unsigned char c)
{
	int	bidx;
	int signal;

	bidx = 7;
	while (bidx >= 0)
	{
		g_ack_received = 0;
		if ((c >> bidx) & 1)
		{
			if ((c >> bidx) & 1)
				signal = SIGUSR1;
			else
				signal = SIGUSR2;
			if (kill(server_pid, signal) == -1)
			{
				ft_printf("Error: Invalid PID\n");
				exit(1);
			}
		}
		while (!g_ack_received)
			pause();
		bidx--;
	}
}

static void	client_action(char *msg, pid_t server_pid)
{
	struct sigaction	sa;
	int					midx;

	sa.sa_handler = ack_handler;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	midx = 0;
	while (msg[midx])
	{
		send_byte_and_wait(server_pid, msg[midx]);
		midx++;
	}
	send_byte_and_wait(server_pid, '\0');
}

int	main(int argc, char **argv)
{
	pid_t	server_pid;

	if (argc != 3)
	{
		ft_printf("Error.\nCheck the arguments\n ");
		return (1);
	}
	server_pid = ft_atoi(argv[1]);
	if (server_pid <= 0)
	{
		ft_printf("Error: Invalid Server PID.\n");
		return (1);
	}
	client_action(argv[2], server_pid);
	return (0);
}
