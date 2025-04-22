/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmunier <nmunier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 15:29:09 by nmunier           #+#    #+#             */
/*   Updated: 2025/04/15 16:10:37 by nmunier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <my_threads.h>

static size_t	get_str_size(int n, unsigned int *abs, unsigned int *power)
{
	size_t	str_size;

	*power = 1;
	str_size = 1;
	if (n < 0)
		*abs = -n;
	else
		*abs = n;
	while (*abs / *power >= 10)
	{
		*power *= 10;
		str_size++;
	}
	if (n < 0)
		str_size++;
	return (++str_size);
}

char	*ft_itoa(int n)
{
	unsigned int	power;
	char			*str;
	size_t			len;
	size_t			start;
	unsigned int	abs;

	len = get_str_size(n, &abs, &power);
	str = malloc(len * sizeof(char));
	if (!str)
		return (NULL);
	start = 0;
	if (n < 0)
	{
		str[0] = '-';
		start = 1;
	}
	while (start < len - 1)
	{
		str[start++] = abs / power + '0';
		abs = abs % power;
		power = power / 10;
	}
	str[len - 1] = '\0';
	return (str);
}