/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccavalca <ccavalca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 00:04:35 by ccavalca          #+#    #+#             */
/*   Updated: 2025/11/25 14:49:14 by ccavalca         ###   ########.fr       */
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

#endif