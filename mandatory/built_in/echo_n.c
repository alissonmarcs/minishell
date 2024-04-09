/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_n.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matesant <matesant@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 12:11:27 by matesant          #+#    #+#             */
/*   Updated: 2024/04/09 17:14:36 by matesant         ###   ########.fr       */
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
	if (!argv[i])
	{
		if (!flag)
			ft_printf_fd(STDOUT_FILENO, "\n");
		return ;
	}
	while (argv[i])
	{
		ft_printf_fd(STDOUT_FILENO, "%s", argv[i]);
		if (argv[i + 1])
			ft_printf_fd(STDOUT_FILENO, " ");
		i++;
	}
	if (!flag)
		write(1, "\n", 1);
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
