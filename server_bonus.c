/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccavalca <ccavalca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 00:04:00 by ccavalca          #+#    #+#             */
/*   Updated: 2025/10/30 15:02:46 by ccavalca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static void	signal_handler(int signal)
{
	int				i;
	unsigned char	current_char;
	int				bidx;

	current_char = 0;
	i = 0;
	if (i < 0)
		return ;
	if (signal == SIGUSR2)
		current_char |= (1 << bit);
	bit++;
	if (bit == 8)
	{
		write (1, &current_char, 1);
		current_char = 0;
		bit = 0;
	}
}
