/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccavalca <ccavalca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 15:06:44 by ccavalca          #+#    #+#             */
/*   Updated: 2025/10/29 17:20:50 by ccavalca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"



int	main(int argc, char **argv)
{
	if(argc != 1)
		ft_printf("Error\n");
		return ;
	ft_printf("PID: %p", getpid());
}
