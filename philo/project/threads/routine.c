/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmunier <nmunier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 15:30:04 by nmunier           #+#    #+#             */
/*   Updated: 2025/04/11 19:13:44 by nmunier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <my_threads.h>

void	*routine_philo(void *philosopher)
{
	t_philosopher	*philo;

	philo = (t_philosopher *) philosopher;
	pthread_mutex_lock(philo->last_meal_time_mutex);
	philo->last_meal_time = get_local_time(philo->table);
	pthread_mutex_unlock(philo->last_meal_time_mutex);
	if (philo->table->num_of_philosophers == 1)
		return (printf_philosopher(philo, FORK_TAKEN_MSG, philo->table), \
				ft_sleep(philo->table->time_to_die, philo->table), \
				printf_philosopher(philo, DIED_MSG, philo->table), NULL);
	while (true)
	{
		think(philo);
		eat(philo);
		rest(philo);
		if (has_simulation_ended(philo->table))
		{
			release_fork(philo);
			release_fork(philo->next_philosopher);
			break ;
		}
	}
	return (NULL);
}

void	*routine_reaper(void *table_ptr)
{
	t_table	*table;

	table = (t_table *) table_ptr;
	while (true)
	{
		if (reap(table) || check_end_condition(table))
		{
			pthread_mutex_lock(table->end_simulation_mutex);
			table->is_simulation_running = false;
			pthread_mutex_unlock(table->end_simulation_mutex);
			return (NULL);
		}
		usleep(100);
	}
	return (NULL);
}
