/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmunier <nmunier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 18:35:21 by nmunier           #+#    #+#             */
/*   Updated: 2025/04/07 18:35:34 by nmunier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <my_threads.h>

void	change_state(t_philosopher *philo, t_state new_state)
{
	if (philo->state != is_dead)
		philo->state = new_state;
}

t_state	get_state(t_philosopher *philo)
{
	t_state	state;

	sem_wait(philo->state_sem);
	state = philo->state;
	sem_post(philo->state_sem);
	return (state);
}

t_boolean	get_has_eaten(t_philosopher *philo)
{
	t_boolean	has_eaten;

	has_eaten = false;
	if (philo->meal_count == philo->table->nb_meals_to_eat \
		&& philo->table->nb_meals_to_eat > 0)
		has_eaten = true;
	return (has_eaten);
}

t_boolean	grab_fork(t_philosopher *philo)
{
	if (!philo || get_is_dead(philo))
		return (false);
	sem_wait(philo->forks_sem);
	if (get_is_dead(philo))
		return (sem_post(philo->forks_sem), false);
	philo->fork_count += 1;
	return (true);
}

t_boolean	release_fork(t_philosopher *philo)
{
	if (!philo || get_is_dead(philo))
		return (false);
	if (philo->fork_count > 0)
	{
		sem_post(philo->forks_sem);
		philo->fork_count -= 1;
	}
	return (true);
}