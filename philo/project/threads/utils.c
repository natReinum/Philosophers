/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmunier <nmunier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 18:24:55 by nmunier           #+#    #+#             */
/*   Updated: 2025/04/18 17:47:29 by nmunier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <my_threads.h>

void	printf_philosopher(t_philosopher *philosopher, \
							char *str, t_table *table)
{
	pthread_mutex_lock(philosopher->printf_mutex);
	if (has_simulation_ended(table) == false || str[14] == 'd')
		printf(str, get_local_time(table), philosopher->id);
	pthread_mutex_unlock(philosopher->printf_mutex);
}

time_t	get_timestamp(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

time_t	get_local_time(t_table *table)
{
	return (get_timestamp() - table->start_time);
}

void	ft_sleep(time_t mili_s, t_table *table)
{
	time_t	end;

	end = get_timestamp() + mili_s;
	while (get_timestamp() < end)
	{
		if (has_simulation_ended(table))
			break ;
		usleep(100);
	}
}

time_t	min(time_t a, time_t b)
{
	if (a < b)
		return (a);
	return (b);
}
