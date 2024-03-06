/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matesant <matesant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 15:37:46 by matesant          #+#    #+#             */
/*   Updated: 2023/08/13 15:13:19 by matesant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_count(long n)
{
	long	digits;

	digits = 0;
	if (n <= 0)
	{
		digits++;
	}
	while (n)
	{
		digits++;
		n = n / 10;
	}
	return (digits);
}

char	*ft_itoa(int n)
{
	long	nb;
	char	*newit;
	size_t	len;

	len = ft_count(n);
	nb = n;
	newit = (char *)malloc((len + 1) * sizeof(char));
	if (newit == NULL)
		return (NULL);
	if (nb == 0)
		newit[0] = '0';
	if (nb < 0)
	{
		newit[0] = '-';
		nb *= -1;
	}
	newit[len] = '\0';
	len--;
	while (nb)
	{
		newit[len] = (nb % 10) + '0';
		nb = nb / 10;
		len--;
	}
	return (newit);
}
