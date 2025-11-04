/* pipe used to transfer completed bytes from signal handler to main loop */
static int		g_pipefd[2] = {-1, -1};
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccavalca <ccavalca@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 00:03:44 by ccavalca          #+#    #+#             */
/*   Updated: 2025/11/03 00:29:54 by ccavalca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static int	find_or_create_client(pid_t pid)
{
	int	i;
	t_client_state	client;

	client.pid = 0;
	if (pid <= 0)
		return (-1);
	i = 0;
	while (i < MAX_CLIENTS)
	{
		if (client.pid == pid)
			return (i);
		if (client.pid == 0)
		{
			client.pid = pid;
			client.current_char = 0;
			client.bit = 0;
			return (i);
		}
		i++;
	}
	return (-1);
}

static void	signal_handler(int signal, siginfo_t *info, void *ucontext)
{
	int				i;
	t_client_state	client;

	client.pid = 0;
	find_or_create_client(client.pid);
	(void)ucontext;
	if (!info)
		return ;
	client.pid = info->si_pid;
	i = find_or_create_client(client.pid);
	if (i < 0)
		return ;
	if (signal == SIGUSR1)
		client.current_char |= (1 << client.bit);
	client.bit++;
	kill(client.pid, SIGUSR1);
	if (client.bit == 8)
	{
		if (client.current_char == '\0')
			write(1, "\n", 1);
		else
			write(1, &client.current_char, 1);
		client.current_char = 0;
		client.bit = 0;
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
	char	c;

	ft_printf("PID: %d\n", getpid());
	signal_action();
	while (1)
	{
		if (read(g_pipefd[0], &c, 1) == 1)
			write(1, &c, 1);
	}
	return (0);
}
