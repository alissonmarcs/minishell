/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matesant <matesant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 18:31:27 by matesant          #+#    #+#             */
/*   Updated: 2024/03/05 18:43:33 by matesant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_change_spaces(char *line)
{
	int	i;

	i = 0;
	if (line[i] == ' ')
		i++;
	while (line[i])
	{
		if (line[i] == ' ')
			line[i] = '.';
		i++;
	}
}

void	ft_tokenize(char *line)
{
	ft_change_spaces(line);
}
