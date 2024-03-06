/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_hex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matesant <matesant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 15:27:05 by matesant          #+#    #+#             */
/*   Updated: 2023/09/20 15:27:17 by matesant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_validate_pointer(unsigned long hex, int *count)
{
	if (hex == 0)
	{
		*count += write(1, "(nil)", 5);
		return ;
	}
	ft_validate_str("0x", count);
	ft_validate_hex(hex, count, 'x');
}

void	ft_validate_hex(unsigned long pointer, int *count, char x_x)
{
	char	str[25];
	char	*base_hex;
	int		i;

	if (x_x == 'X')
		base_hex = "0123456789ABCDEF";
	else
		base_hex = "0123456789abcdef";
	if (pointer == 0)
	{
		ft_putchar('0', count);
		return ;
	}
	i = 0;
	while (pointer)
	{
		str[i] = base_hex[pointer % 16];
		pointer /= 16;
		i++;
	}
	while (i--)
		ft_putchar(str[i], count);
}
