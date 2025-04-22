/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmunier <nmunier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 15:40:20 by nmunier           #+#    #+#             */
/*   Updated: 2025/04/18 20:03:56 by nmunier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <my_threads.h>

void	think(t_philosopher *philo)
{
	time_t	thinking_time;

	if (get_is_dead(philo) || get_state(philo) != is_thinking)
		return ;
	sem_wait(philo->state_sem);
	thinking_time = philo->table->time_to_die \
					- (get_local_time(philo->table) - philo->last_meal_time) \
					- philo->table->time_to_eat;
	sem_post(philo->state_sem);
	thinking_time /= 2;
	if (thinking_time < 0)
		thinking_time = 0;
	printf_philosopher(philo, THINKING_MSG, philo->table);
	ft_sleep(thinking_time, philo);
	change_state(philo, is_eating);
}

void	eat(t_philosopher *philo)
{
	if (get_is_dead(philo) || get_state(philo) != is_eating)
		return ;
	t_boolean (fork_right) = grab_fork(philo);
	t_boolean (fork_left) = grab_fork(philo);
	if (fork_right)
		printf_philosopher(philo, FORK_TAKEN_MSG, philo->table);
	if (fork_left)
		printf_philosopher(philo, FORK_TAKEN_MSG, philo->table);
	if (fork_right && fork_left)
	{
		printf_philosopher(philo, EATING_MSG, philo->table);
		sem_wait(philo->state_sem);
		philo->last_meal_time = get_local_time(philo->table);
		sem_post(philo->state_sem);
		ft_sleep(min(philo->table->time_to_eat, philo->table->time_to_die), \
			philo);
		philo->meal_count += 1;
	}
	(release_fork(philo), release_fork(philo), \
	change_state(philo, is_sleeping));
}

void	rest(t_philosopher *philo)
{
	if (get_is_dead(philo) || get_state(philo) != is_sleeping)
		return ;
	printf_philosopher(philo, SLEEPING_MSG, philo->table);
	ft_sleep(philo->table->time_to_sleep, philo);
	change_state(philo, is_thinking);
}
