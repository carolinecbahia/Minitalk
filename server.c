/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccavalca <ccavalca@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 00:03:44 by ccavalca          #+#    #+#             */
/*   Updated: 2025/10/31 01:17:28 by ccavalca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static t_client_state	g_clients[MAX_CLIENTS];

static int	find_or_create_client(pid_t pid)
{
	int	i;

	if (pid <= 0)
		return (-1);
	i = 0;
	while (i < MAX_CLIENTS)
	{
		if (g_clients[i].pid == pid)
			return (i);
		if (g_clients[i].pid == 0)
		{
			g_clients[i].pid = pid;
			g_clients[i].current_char = 0;
			g_clients[i].bit = 0;
			return (i);
		}
		i++;
	}
	return (-1);
}

static void	signal_handler(int signal, siginfo_t *info, void *ucontext)
{
	int		i;
	pid_t	sender;

	(void)ucontext;
	if (!info)
		return ;
	sender = info->si_pid;
	i = find_or_create_client(sender);
	if (i < 0)
		return ;
	if (signal == SIGUSR2)
		g_clients[i].current_char |= (1 << g_clients[i].bit);
	g_clients[i].bit++;
	if (g_clients[i].bit == 8)
	{
		write (1, &g_clients[i].current_char, 1);
		g_clients[i].current_char = 0;
		g_clients[i].bit = 0;
		kill(sender, SIGUSR1);
	}
}

static void	signal_action(void)
{
	struct sigaction	act;

	ft_bzero(&act, sizeof(act));
	act.sa_sigaction = signal_handler;
	act.sa_flags = SA_SIGINFO;
	sigemptyset(&act.sa_mask);
	sigaction(SIGUSR1, &act, NULL);
	sigaction(SIGUSR2, &act, NULL);
}

int	main(void)
{	
	ft_printf("PID: %d\n", getpid());
	signal_action();
	while (1)
		pause();
	return (0);
}
