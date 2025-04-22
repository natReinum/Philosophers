/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmunier <nmunier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 15:40:20 by nmunier           #+#    #+#             */
/*   Updated: 2025/04/18 16:46:14 by nmunier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <my_threads.h>

void	think(t_philosopher *philo)
{
	time_t	thinking_time;

	if (get_is_dead(philo) || get_state(philo) != is_thinking \
		|| has_simulation_ended(philo->table))
		return ;
	pthread_mutex_lock(philo->last_meal_time_mutex);
	thinking_time = philo->table->time_to_die \
					- (get_local_time(philo->table) - philo->last_meal_time) \
					- philo->table->time_to_eat;
	pthread_mutex_unlock(philo->last_meal_time_mutex);
	thinking_time /= 2;
	if (thinking_time < 0)
		thinking_time = 0;
	pthread_mutex_lock(philo->state_mutex);
	if (philo->last_state != is_thinking)
		printf_philosopher(philo, THINKING_MSG, philo->table);
	pthread_mutex_unlock(philo->state_mutex);
	ft_sleep(thinking_time, philo->table);
	change_state(philo, is_eating);
}

void	eat(t_philosopher *philo)
{
	if (get_is_dead(philo) || get_state(philo) != is_eating \
		|| has_simulation_ended(philo->table))
		return ;
	t_boolean (fork_right) = grab_fork(philo);
	t_boolean (fork_left) = grab_fork(philo->next_philosopher);
	if (fork_right)
		printf_philosopher(philo, FORK_TAKEN_MSG, philo->table);
	if (fork_left)
		printf_philosopher(philo, FORK_TAKEN_MSG, philo->table);
	if (fork_right && fork_left)
	{
		printf_philosopher(philo, EATING_MSG, philo->table);
		pthread_mutex_lock(philo->last_meal_time_mutex);
		philo->last_meal_time = get_local_time(philo->table);
		pthread_mutex_unlock(philo->last_meal_time_mutex);
		ft_sleep(min(philo->table->time_to_eat, philo->table->time_to_die), \
			philo->table);
		pthread_mutex_lock(philo->meal_count_mutex);
		philo->meal_count += 1;
		pthread_mutex_unlock(philo->meal_count_mutex);
	}
	(release_fork(philo), release_fork(philo->next_philosopher), \
		change_state(philo, is_sleeping));
}

void	rest(t_philosopher *philo)
{
	if (get_is_dead(philo) || get_state(philo) != is_sleeping \
		|| has_simulation_ended(philo->table))
		return ;
	printf_philosopher(philo, SLEEPING_MSG, philo->table);
	ft_sleep(philo->table->time_to_sleep, philo->table);
	change_state(philo, is_thinking);
}
