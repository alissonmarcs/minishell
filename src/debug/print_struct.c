/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_struct.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matesant <matesant@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 15:24:03 by matesant          #+#    #+#             */
/*   Updated: 2024/04/03 06:18:37 by matesant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_translate_type(int type, int i)
{
	printf("| Type [%d]:", i);
	if (type == 1)
		printf("SPACES \n");
	else if (type == 2)
		printf("VAR \n");
	else if (type == 3)
		printf("WORD \n");
	else if (type == 4)
		printf("PIPE \n");
	else if (type == 5)
		printf("INPUT \n");
	else if (type == 6)
		printf("TRUNC \n");
	else if (type == 7)
		printf("APPEND \n");
	else if (type == 8)
		printf("HERE_DOC \n");
	else if (type == 9)
		printf("END \n");
}

void	ft_print_stack(t_token *stack)
{
	int	i;

	i = 0;
	while (stack)
	{
		printf("-----------------------------\n");
		printf("| Token[%d]:%s.\n", i, stack->str);
		ft_translate_type(stack->type, i);
		printf("| Stack[%d]:%p\n", i, stack);
		printf("| Next [%d]:%p\n", i, stack->next);
		printf("| Prev [%d]:%p\n", i, stack->prev);
		printf("-----------------------------\n");
		i++;
		stack = stack->next;
	}
}

void	ft_print_env_list(t_env *env_list)
{
	int	i;

	i = 0;
	while (env_list)
	{
		printf("-----------------------------\n");
		printf("| Key[%d]:%s.\n", i, env_list->key);
		printf("| Value[%d]:%s.\n", i, env_list->value);
		printf("| Next [%d]:%p\n", i, env_list->next);
		printf("-----------------------------\n");
		i++;
		env_list = env_list->next;
	}
}

void	ft_print_matrice(char **matrice)
{
	int	i;

	i = 0;
	while (matrice[i])
	{
		printf("-----------------------------\n");
		printf("| Matrice[%d]:%s.\n", i, matrice[i]);
		printf("-----------------------------\n");
		i++;
	}
}
