/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccavalca <ccavalca@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 00:04:21 by ccavalca          #+#    #+#             */
/*   Updated: 2025/10/30 03:10:52 by ccavalca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#include <stdio.h>

volatile sig_atomic_t	g_ack_received;

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*ptr;

	i = 0;
	ptr = (unsigned char *)s;
	while (i < n)
	{
		ptr[i++] = (unsigned char)c;
	}
	return (s);
}

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}

int	ft_atoi(const char *nptr)
{
	int	i;
	int	sign;
	int	nb;

	i = 0;
	sign = 1;
	nb = 0;
	while (nptr[i] == ' ' || (nptr[i] >= '\t' && nptr[i] <= '\r'))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign = -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		nb = nb * 10 + (nptr[i] - '0');
		i++;
	}
	return (nb * sign);
}

static void	ack_handler(int sig)
{
	(void)sig;
	g_ack_received = 1;
}

static void	send_char_bits(__pid_t server_pid, unsigned char c)
{
	unsigned int i;

	i = 0;
	while (i < 8)
	{
		if ((c >> i) & 1)
			kill(server_pid, SIGUSR2);
		else
			kill(server_pid, SIGUSR1);
		usleep(3500);
		i++;
	}
}

int	main(int argc, char **argv)
{
	struct sigaction	sa;
	sigset_t	mask, oldmask;
	__pid_t			server_pid;
	unsigned char	c;
	int				i;

	if (argc != 3)
	{
		printf("Error.\nCheck the arguments\n");
		return (1);
	}
	if (argv[1])
		server_pid = ft_atoi(argv[1]);
	else
	{
		printf("Error.\nCheck the arguments\n");
		return (1);
	}
	ft_bzero(&sa, sizeof(sa));
	sa.sa_handler = ack_handler;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);
	sigemptyset(&mask);
	sigaddset(&mask, SIGUSR1);
	sigprocmask(SIG_BLOCK, &mask, &oldmask);
	i = 0;
	while (argv[2][i])
	{
		c = argv[2][i];
		g_ack_received = 0;
		send_char_bits(server_pid, c);
		while (!g_ack_received)
			sigsuspend(&oldmask);
		i++;
	}
	g_ack_received = 0;
	send_char_bits(server_pid, '\n');
	while (!g_ack_received)
		sigsuspend(&oldmask);
	sigprocmask(SIG_SETMASK, &oldmask, NULL);
	return (0);
}
