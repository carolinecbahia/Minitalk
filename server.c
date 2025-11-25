/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccavalca <ccavalca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 00:03:44 by ccavalca          #+#    #+#             */
/*   Updated: 2025/11/23 14:41:53 by ccavalca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static t_client_state	g_clients[MAX_CLIENTS];

static int	find_or_create_client(pid_t pid)
{
	int				i;

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
	g_clients[i].current_char = ((unsigned char)
			(g_clients[i].current_char << 1) | (signal == SIGUSR1));
	g_clients[i].bit++;
	if (g_clients[i].bit == 8)
	{
		if (g_clients[i].current_char == '\0')
			write(1, "\n", 1);
		else
			write(1, &g_clients[i].current_char, 1);
		g_clients[i].current_char = 0;
		g_clients[i].bit = 0;
	}
	kill(sender, SIGUSR1);
}

static void	signal_action(void)
{
	struct sigaction	sa;

	sa.sa_sigaction = signal_handler;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGUSR1);
	sigaddset(&sa.sa_mask, SIGUSR2);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
}

int	main(void)
{
	ft_bzero(g_clients, sizeof(t_client_state) * MAX_CLIENTS);
	ft_printf("PID: %d\n", getpid());
	signal_action();
	while (1)
	{
		pause();
	}
	return (0);
}
