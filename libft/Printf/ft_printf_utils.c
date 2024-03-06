/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matesant <matesant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 15:26:37 by matesant          #+#    #+#             */
/*   Updated: 2023/09/20 15:26:50 by matesant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putchar(int c, int *count)
{
	*count += write(1, &c, 1);
}

void	ft_validate_str(char *str, int *count)
{
	int	i;

	i = 0;
	if (!str)
	{
		*count += write(1, "(null)", 6);
		return ;
	}
	while (str[i])
	{
		ft_putchar(str[i], count);
		i++;
	}
}

void	ft_validate_nbr(long n, int *count)
{
	if (n < 0)
	{
		n = -n;
		ft_putchar(('-'), count);
	}
	if (n >= 10)
		ft_validate_nbr(n / 10, count);
	ft_putchar(n % 10 + 48, count);
}

void	ft_validate_unsigned(unsigned int n, int *count)
{
	if (n >= 10)
		ft_validate_nbr(n / 10, count);
	ft_putchar(n % 10 + 48, count);
}
