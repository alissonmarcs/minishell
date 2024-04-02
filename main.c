/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matesant <matesant@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 17:19:56 by matesant          #+#    #+#             */
/*   Updated: 2024/04/02 12:57:21 by matesant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

// t_minishell	*ft_get_shell(void)
// {
// 	static t_minishell	shell;

// 	return (&shell);
// }
int	main(void)
{
	char	*line;

	line = "=";
	line++;
	printf("%p\n", line);
	return (0);
}
