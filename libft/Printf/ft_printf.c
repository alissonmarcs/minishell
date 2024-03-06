/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matesant <matesant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 15:25:49 by matesant          #+#    #+#             */
/*   Updated: 2023/09/20 15:26:00 by matesant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_validate(va_list args, const char *format, int *count, int *i)
{
	if (format[*i] == '%')
		ft_putchar('%', count);
	else if (format[*i] == 'c')
		ft_putchar(va_arg(args, int), count);
	else if (format[*i] == 's')
		ft_validate_str(va_arg(args, char *), count);
	else if ((format[*i] == 'd') || (format[*i] == 'i'))
		ft_validate_nbr(va_arg(args, int), count);
	else if (format[*i] == 'u')
		ft_validate_unsigned(va_arg(args, unsigned int), count);
	else if (format[*i] == 'p')
		ft_validate_pointer(va_arg(args, unsigned long), count);
	else if (format[*i] == 'x')
		ft_validate_hex(va_arg(args, unsigned int), count, 'x');
	else if (format[*i] == 'X')
		ft_validate_hex(va_arg(args, unsigned int), count, 'X');
	*i += 1;
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		i;
	int		count;

	i = 0;
	count = 0;
	if (!format)
		return (-1);
	va_start(args, format);
	while (format[i])
	{
		if (format[i] != '%')
		{
			ft_putchar(format[i++], &count);
		}
		else
		{
			i++;
			ft_validate(args, format, &count, &i);
		}
	}
	va_end(args);
	return (count);
}
