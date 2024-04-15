/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_delete_matrice.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matesant <matesant@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 12:45:24 by matesant          #+#    #+#             */
/*   Updated: 2024/03/28 12:08:19 by matesant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_delete_matrice(char **matrice)
{
	int	i;

	if (!matrice)
		return ;
	i = 0;
	while (matrice[i])
	{
		free(matrice[i]);
		i++;
	}
	free(matrice);
	matrice = NULL;
}

int	ft_matrice_len(char **matrice)
{
	int	i;

	i = 0;
	while (matrice[i])
		i++;
	return (i);
}
