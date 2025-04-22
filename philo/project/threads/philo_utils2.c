/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmunier <nmunier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 18:35:21 by nmunier           #+#    #+#             */
/*   Updated: 2025/04/18 17:19:58 by nmunier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <my_threads.h>

void	change_state(t_philosopher *philo, t_state new_state)
{
	pthread_mutex_lock(philo->state_mutex);
	philo->last_state = philo->state;
	if (philo->state != is_dead)
		philo->state = new_state;
	pthread_mutex_unlock(philo->state_mutex);
}

t_state	get_state(t_philosopher *philo)
{
	t_state	state;

	pthread_mutex_lock(philo->state_mutex);
	state = philo->state;
	pthread_mutex_unlock(philo->state_mutex);
	return (state);
}

t_boolean	get_has_eaten(t_philosopher *philo)
{
	t_boolean	has_eaten;

	has_eaten = false;
	pthread_mutex_lock(philo->meal_count_mutex);
	if (philo->meal_count >= philo->table->nb_meals_to_eat \
		&& philo->table->nb_meals_to_eat > 0)
		has_eaten = true;
	pthread_mutex_unlock(philo->meal_count_mutex);
	return (has_eaten);
}

t_boolean	grab_fork(t_philosopher *philo)
{
	if (!philo || get_is_dead(philo) || has_simulation_ended(philo->table))
		return (false);
	pthread_mutex_lock(philo->r_fork_mutex);
	if (get_is_dead(philo) || has_simulation_ended(philo->table))
		return (pthread_mutex_unlock(philo->r_fork_mutex), false);
	return (true);
}

t_boolean	release_fork(t_philosopher *philo)
{
	pthread_mutex_unlock(philo->r_fork_mutex);
	return (true);
}
