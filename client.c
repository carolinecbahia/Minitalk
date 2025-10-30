/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccavalca <ccavalca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 00:04:21 by ccavalca          #+#    #+#             */
/*   Updated: 2025/10/30 17:13:01 by ccavalca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

volatile sig_atomic_t	g_ack_received;

static void	ack_handler(int signal)
{
	(void)signal;
	g_ack_received = 1;
}

static void	send_char_bits(pid_t server_pid, unsigned char c)
{
	unsigned int	bidx;

	bidx = 0;
	while (bidx < 8)
	{
		if ((c >> bidx) & 1)
			kill(server_pid, SIGUSR2);
		else
			kill(server_pid, SIGUSR1);
		bidx++;
	}
}

static void	client_action(char *msg, pid_t server_pid)
{
	struct sigaction	sa;
	sigset_t			mask;
	sigset_t			oldmask;
	int					midx;

	ft_bzero(&sa, sizeof(sa));
	sa.sa_handler = ack_handler;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);
	sigemptyset(&mask);
	sigaddset(&mask, SIGUSR1);
	sigprocmask(SIG_BLOCK, &mask, &oldmask);
	midx = 0;
	while (msg[midx])
	{
		g_ack_received = 0;
		send_char_bits(server_pid, msg[midx]);
		while (!g_ack_received)
			sigsuspend(&oldmask);
		midx++;
	}
	g_ack_received = 0;
	while (!g_ack_received)
		sigsuspend(&oldmask);
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
	if (argv[1])
		server_pid = ft_atoi(argv[1]);
	else
	{
		ft_printf("Error.\nCheck the arguments\n");
		return (1);
	}
	client_action(argv[2], server_pid);
	send_char_bits(server_pid, '\n');
	return (0);
}
