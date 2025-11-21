/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccavalca <ccavalca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 00:04:13 by ccavalca          #+#    #+#             */
/*   Updated: 2025/11/21 16:48:08 by ccavalca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

volatile sig_atomic_t	g_ack_received;

static void	ack_handler(int signal)
{
	(void)signal;
	g_ack_received = 1;
}

void	send_byte_and_wait(pid_t server_pid, unsigned char c, sigset_t *oldmask)
{
	int	bidx;

	bidx = 7;
	while (bidx >= 0)
	{
		g_ack_received = 0;
		if ((c >> bidx) & 1)
			kill(server_pid, SIGUSR1);
		else
			kill(server_pid, SIGUSR2);
		while (!g_ack_received)
			sigsuspend(oldmask);
		bidx--;
	}
}

static void	end_handler(int signal)
{
	(void)signal;
	ft_printf("\nSucesso: O servidor confirmou o recebimento da mensagem!\n");
	exit(0);
}

static void	client_action(char *msg, pid_t server_pid)
{
	struct sigaction	sa_ack;
	struct sigaction	sa_end;
	sigset_t			oldmask;
	int					midx;

	sa_ack.sa_handler = ack_handler;
	sa_ack.sa_flags = 0;
	sigemptyset(&sa_ack.sa_mask);
	sigaction(SIGUSR1, &sa_ack, NULL);
	sa_end.sa_handler = end_handler;
	sa_end.sa_flags = 0;
	sigemptyset(&sa_end.sa_mask);
	sigaction(SIGUSR1, &sa_end, NULL);
	midx = 0;
	while (msg[midx])
	{
		send_byte_and_wait(server_pid, msg[midx], &oldmask);
		midx++;
	}
	send_byte_and_wait(server_pid, '\0', &oldmask);
	sigprocmask(SIG_SETMASK, &oldmask, NULL);
}

int	main(int argc, char **argv)
{
	pid_t				server_pid;

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
