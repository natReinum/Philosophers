/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmunier <nmunier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 18:24:55 by nmunier           #+#    #+#             */
/*   Updated: 2025/04/14 17:02:53 by nmunier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <my_threads.h>

void	printf_philosopher(t_philosopher *philosopher, \
							char *str, t_table *table)
{
	sem_wait(philosopher->printf_sem);
	if (!get_is_dead(philosopher))
		printf(str, get_local_time(table), philosopher->id);
	sem_post(philosopher->printf_sem);
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

void	ft_sleep(time_t mili_s, t_philosopher *philosopher)
{
	time_t	end;

	end = get_timestamp() + mili_s;
	while (get_timestamp() < end)
	{
		if (get_is_dead(philosopher))
			return ;
		usleep(100);
	}
}

time_t	min(time_t a, time_t b)
{
	if (a < b)
		return (a);
	return (b);
}