/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccavalca <ccavalca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 00:04:35 by ccavalca          #+#    #+#             */
/*   Updated: 2025/10/30 16:39:20 by ccavalca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <signal.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/types.h>
# include "Libft/libft.h"
# include "ft_printf/ft_printf.h"

# define MAX_CLIENTS 256

// Structs
typedef struct s_client_state
{
	pid_t			pid;
	unsigned char	current_char;
	int				bit;
}	t_client_state;

// Libraries
int		ft_printf(const char *print, ...);
void	*ft_memset(void *s, int c, size_t n);
void	ft_bzero(void *s, size_t n);
int		ft_atoi(const char *nptr);

// Signal handlers

#endif