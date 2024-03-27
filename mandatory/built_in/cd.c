/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matesant <matesant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 16:57:33 by matesant          #+#    #+#             */
/*   Updated: 2024/03/27 13:01:28 by matesant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cd_builtin(char **argv)
{
	char	*path;

	if (!argv || !argv[1] || !argv[1][0] || !ft_strncmp(argv[1], " ", 1)
		|| !ft_strncmp(argv[1], "--", 3) || !ft_strncmp(argv[1], "~", 2))
	{
		path = ft_getenv("HOME");
		if (!path)
		{
			ft_error("cd: HOME not set", 1);
			return ;
		}
	}
	else
		path = argv[1];
	chdir(path);
}
