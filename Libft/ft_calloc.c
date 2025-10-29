/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccavalca <ccavalca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 16:25:19 by ccavalca          #+#    #+#             */
/*   Updated: 2025/07/18 19:55:39 by ccavalca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	total;
	void	*aloc;

	if (nmemb > 0 && size > 0 && nmemb > (__SIZE_MAX__ / size))
		return (NULL);
	total = nmemb * size;
	aloc = malloc(total);
	if (aloc == NULL)
		return (NULL);
	ft_bzero(aloc, total);
	return (aloc);
}
