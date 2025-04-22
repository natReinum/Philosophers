/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmunier <nmunier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 17:20:39 by nmunier           #+#    #+#             */
/*   Updated: 2025/04/07 16:05:48 by nmunier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <checker.h>

static void	print_usage(void)
{
	printf("Usage: ./philo number_of_philosophers time_to_die " \
	"time_to_eat time_to_sleep " \
	"[number_of_times_each_philosopher_must_eat]\n\033[0;91m!!!!" \
	" All values must be positive !!!!\033[0;39m\n");
}

static t_boolean	is_number(char *str)
{
	if (*str == '-' || *str == '+')
		str++;
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (false);
		str++;
	}
	return (true);
}

t_boolean	input_checker(int argc, char **argv, int *philo_nb, double *times)
{
	if (argc != 5 && argc != 6)
	{
		print_usage();
		return (false);
	}
	*philo_nb = ft_atoi(argv[1]);
	times[0] = ft_atoi(argv[2]);
	times[1] = ft_atoi(argv[3]);
	times[2] = ft_atoi(argv[4]);
	if (argc == 6)
		times[3] = ft_atoi(argv[5]);
	else
		times[3] = 0;
	if (times[0] <= 0 || times[1] <= 0 || times[2] <= 0 || times[3] < 0 \
		|| *philo_nb <= 0 \
		|| !is_number(argv[1]) || !is_number(argv[2]) \
		|| !is_number(argv[3]) || !is_number(argv[4]) \
		|| (argc == 6 && !is_number(argv[5])))
		return (print_usage(), false);
	return (true);
}
