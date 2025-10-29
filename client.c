/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccavalca <ccavalca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 15:06:41 by ccavalca          #+#    #+#             */
/*   Updated: 2025/10/29 18:19:29 by ccavalca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#include <stdio.h>

int	main(int argc, char **argv)
{
	if (argc != 2)
	{
		printf("Error.\n The string must be bt \" \" ");
	}
	else
	printf("Teste de validação: %s", argv[1]);
	
}
