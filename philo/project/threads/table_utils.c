/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmunier <nmunier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 17:47:32 by nmunier           #+#    #+#             */
/*   Updated: 2025/04/18 17:38:02 by nmunier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <my_threads.h>

t_boolean	check_end_condition(t_table *table)
{
	int	i;
	int	alive_philo;
	int	philo_sated;

	i = 0;
	alive_philo = 0;
	philo_sated = 0;
	while (i < table->num_of_philosophers)
	{
		if (!get_is_dead(table->philosophers[i]))
			alive_philo++;
		if (get_has_eaten(table->philosophers[i]))
			philo_sated++;
		i++;
	}
	if (alive_philo < table->num_of_philosophers \
		|| philo_sated == table->num_of_philosophers)
		return (true);
	return (false);
}

t_boolean	has_simulation_ended(t_table *table)
{
	t_boolean	has_ended;

	has_ended = false;
	pthread_mutex_lock(table->end_simulation_mutex);
	if (!table->is_simulation_running)
		has_ended = true;
	pthread_mutex_unlock(table->end_simulation_mutex);
	return (has_ended);
}

t_boolean	reap(t_table *table)
{
	int			i;

	i = 0;
	while (i < table->num_of_philosophers)
	{
		pthread_mutex_lock(table->philosophers[i]->last_meal_time_mutex);
		if (get_local_time(table) - table->philosophers[i]->last_meal_time \
			>= table->time_to_die)
		{
			change_state(table->philosophers[i], is_dead);
			pthread_mutex_lock(table->end_simulation_mutex);
			table->is_simulation_running = false;
			pthread_mutex_unlock(table->end_simulation_mutex);
			printf_philosopher(table->philosophers[i], DIED_MSG, table);
			pthread_mutex_unlock(table->philosophers[i]->last_meal_time_mutex);
			return (true);
		}
		pthread_mutex_unlock(table->philosophers[i]->last_meal_time_mutex);
		i++;
	}
	return (false);
}
