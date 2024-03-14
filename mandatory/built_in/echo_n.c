/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_n.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matesant <matesant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 12:11:27 by matesant          #+#    #+#             */
/*   Updated: 2024/03/14 14:51:36 by matesant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_flag(char *arg)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	if (arg[i] != '-')
		return (flag);
	i++;
	while (arg[i])
	{
		if (arg[i] == 'n')
			flag = 1;
		else if (arg[i] != 'n')
		{
			flag = 0;
			return (flag);
		}
		i++;
	}
	return (flag);
}

void	ft_print_args(char **argv, int i, int flag)
{
	int	j;

	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] == '\"')
				j++;
			if (argv[i][j])
				write(1, &argv[i][j], 1);
			j++;
		}
		if (argv[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (!flag)
		write(1, "\n", 2);
}

void	ft_echo_builtin(char **argv)
{
	int	i;
	int	flag;

	i = 1;
	flag = 0;
	while (argv[i] && ft_flag(argv[i]))
	{
		i++;
		flag = 1;
	}
	ft_print_args(argv, i, flag);
}

