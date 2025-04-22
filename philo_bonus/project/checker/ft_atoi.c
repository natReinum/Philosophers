/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmunier <nmunier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 14:11:46 by nmunier           #+#    #+#             */
/*   Updated: 2025/04/22 17:41:12 by nmunier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <checker.h>

static int	ft_isspace(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}

static int	get_sign(const char **nptr)
{
	while (ft_isspace(**nptr))
		(*nptr)++;
	if (**nptr == '-')
	{
		(*nptr)++;
		return (-1);
	}
	else
	{
		if (**nptr == '+')
			(*nptr)++;
		return (1);
	}
}

static int	handle_limits(int sign)
{
	if (sign == 1)
		return (2147483647);
	return (-2147483648);
}

int	ft_atoi(const char *nptr)
{
	int	sum;
	int	sign;
	int	overflow;

	sign = get_sign(&nptr);
	sum = 0;
	overflow = 0;
	while (*nptr >= '0' && *nptr <= '9')
	{
		if (sum > (2147483647 - (*nptr - '0')) / 10)
		{
			overflow = 1;
			break ;
		}
		sum = sum * 10 + (*nptr - '0');
		nptr++;
	}
	if (overflow)
		return (handle_limits(sign));
	return (sum * sign);
}
