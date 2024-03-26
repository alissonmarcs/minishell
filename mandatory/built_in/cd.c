/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matesant <matesant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 16:57:33 by matesant          #+#    #+#             */
/*   Updated: 2024/03/26 15:46:07 by matesant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cd_builtin(char **argv)
{
	char	*path;

	if (!argv || !argv[1] || !argv[1][0] || !ft_strncmp(argv[1], " ", 1)
		|| !ft_strncmp(argv[1], "--", 3))
	{
		path = ft_getenv("HOME");
		printf("cd: %s\n", path);
		// if (!path)
	}
	else
		path = argv[1];
	if (chdir(path) != 0)
		perror("cd");
	else
		printf("cd: %s\n", path);
}
