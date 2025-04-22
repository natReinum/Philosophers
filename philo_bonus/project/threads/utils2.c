/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmunier <nmunier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 15:26:47 by nmunier           #+#    #+#             */
/*   Updated: 2025/04/04 15:29:36 by nmunier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <my_threads.h>

t_boolean	get_is_dead(t_philosopher *philo)
{
	t_boolean	value;

	value = false;
	sem_wait(philo->is_dead_sem);
	if (philo->state == is_dead)
		value = true;
	if (!value && get_local_time(philo->table) - philo->last_meal_time \
			>= philo->table->time_to_die)
		value = true;
	if (value && philo->state != is_dead)
	{
		philo->state = is_dead;
		philo->is_dead = true;
	}
	sem_post(philo->is_dead_sem);
	return (value);
}

void	wait_delay(time_t delay)
{
	while (get_timestamp() < delay)
		usleep(1);
}

t_boolean	has_simulation_ended(t_table *table)
{
	t_boolean	value;

	value = false;
	if (table->is_simulation_running)
		value = true;
	return (value);
}

void	kill_all(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->num_of_philosophers)
		kill(table->pids_philo[i], SIGKILL);
}