/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccavalca <ccavalca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 13:07:13 by ccavalca          #+#    #+#             */
/*   Updated: 2025/07/30 11:37:57 by ccavalca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h" 

t_list	*ft_lstnew(void *content)
{
	t_list	*new;

	new = (t_list *)malloc(sizeof(t_list));
	if (new == NULL)
		return (NULL);
	new->content = content;
	new->next = NULL;
	return (new);
}

// #include "libft.h"
// #include <stdio.h>
// #include <stdlib.h>

// int	main(void)
// {
// 	t_list	*no_string;
// 	t_list	*no_int;
// 	char	*conteudo_str;
// 	int		*conteudo_int;

// 	printf("--- Teste 1: Criar um nó com uma string ---\n");
// 	conteudo_str = "Olá, Libft!";
// 	no_string = ft_lstnew(conteudo_str);
// 	if (!no_string)
// 	{
// 		printf("Erro: ft_lstnew retornou NULL!\n");
// 		return (1);
// 	}
// 	printf("Nó criado com sucesso!\n");
// 	printf("Conteúdo do nó: \"%s\"\n", (char *)no_string->content);
// 	printf("Endereço do próximo nó (next): %p\n", no_string->next);
// 	printf("\n--- Teste 2: Criar um nó com um inteiro ---\n");
// 	conteudo_int = (int *)malloc(sizeof(int));
// 	if (!conteudo_int)
// 	{
// 		printf("Erro: malloc para o inteiro falhou!\n");
// 		free(no_string); // Liberta a memória do teste anterior
// 		return (1);
// 	}
// 	*conteudo_int = 42; // Atribui o valor 42 ao espaço alocado.
// 	no_int = ft_lstnew(conteudo_int);
// 	if (!no_int)
// 	{
// 		printf("Erro: ft_lstnew retornou NULL!\n");
// 		free(no_string);
// 		free(conteudo_int);
// 		return (1);
// 	}
// 	printf("Nó criado com sucesso!\n");
// 	printf("Conteúdo do nó: %d\n", *(int *)no_int->content);
// 	printf("Endereço do próximo nó (next): %p\n", no_int->next);
// 	free(no_string);
// 	free(conteudo_int); // Liberta a memória que alocámos para o inteiro.
// 	free(no_int);
// 	printf("\nMemória libertada com sucesso.\n");
// 	return (0);
// }
