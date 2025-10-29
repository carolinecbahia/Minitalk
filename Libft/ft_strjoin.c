/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccavalca <ccavalca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 18:17:19 by ccavalca          #+#    #+#             */
/*   Updated: 2025/07/19 15:41:53 by ccavalca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *s);

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new_s;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (NULL);
	new_s = (char *)malloc((ft_strlen(s1)) + (ft_strlen(s2)) + 1);
	if (!new_s)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[j])
	{
		new_s[i] = s1[j];
		i++;
		j++;
	}
	j = 0;
	while (s2[j])
	{
		new_s[i++] = s2[j++];
	}
	new_s[i] = '\0';
	return (new_s);
}
