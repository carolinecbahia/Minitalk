/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccavalca <ccavalca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 14:13:03 by ccavalca          #+#    #+#             */
/*   Updated: 2025/07/18 19:56:30 by ccavalca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*ptr_d;
	const unsigned char	*ptr_s;
	size_t				i;

	ptr_d = (unsigned char *)dest;
	ptr_s = (const unsigned char *)src;
	if (ptr_d > ptr_s)
	{
		i = n;
		while (i > 0)
		{
			i--;
			ptr_d[i] = ptr_s[i];
		}
	}
	else
	{
		i = 0;
		while (i < n)
		{
			ptr_d[i] = ptr_s[i];
			i++;
		}
	}
	return (dest);
}
