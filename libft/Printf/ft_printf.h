/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matesant <matesant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 15:26:15 by matesant          #+#    #+#             */
/*   Updated: 2023/09/20 15:26:22 by matesant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>

int		ft_printf(const char *format, ...);
void	ft_putchar(int c, int *count);
void	ft_validate_str(char *str, int *count);
void	ft_validate_nbr(long n, int *count);
void	ft_validate_unsigned(unsigned int n, int *count);
void	ft_validate_hex(unsigned long pointer, int *count, char x_x);
void	ft_validate_pointer(unsigned long hex, int *count);

#endif