/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmunier <nmunier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 15:30:04 by nmunier           #+#    #+#             */
/*   Updated: 2025/04/18 15:32:35 by nmunier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <my_threads.h>

void	*routine_philo(t_philosopher *philo)
{
	wait_delay(philo->table->start_time);
	philo->last_meal_time = get_local_time(philo->table);
	if (philo->table->num_of_philosophers == 1)
		return (printf_philosopher(philo, FORK_TAKEN_MSG, philo->table), \
				ft_sleep(philo->table->time_to_die, philo), \
				printf_philosopher(philo, DIED_MSG, philo->table), NULL);
	while (true)
	{
		think(philo);
		eat(philo);
		if (philo->table->nb_meals_to_eat > 0 && !get_is_dead(philo) \
			&& philo->table->nb_meals_to_eat == philo->meal_count)
			sem_post(philo->has_eaten_sem);
		rest(philo);
		if (get_is_dead(philo))
			break ;
	}
	exit_child(philo);
	return (NULL);
}

void	*routine_first_reaper(void *table_ptr)
{
	int		i;
	int		max;
	t_table	*table;

	table = (t_table *) table_ptr;
	if (table->num_of_philosophers == 1)
		return (NULL);
	wait_delay(table->start_time);
	sem_wait(table->dead_sem);
	kill_all(table);
	i = -1;
	max = table->num_of_philosophers;
	while (++i < max)
		sem_post(table->completed_meals_sem);
	return (NULL);
}

void	*routine_third_reaper(void *table_ptr)
{
	t_table	*table;

	table = (t_table *) table_ptr;
	if (table->num_of_philosophers == 1)
		return (NULL);
	table->is_simulation_running = true;
	table->completed_meals_count = 0;
	wait_delay(table->start_time);
	while (table->is_simulation_running)
	{
		sem_wait(table->completed_meals_sem);
		table->completed_meals_count += 1;
		if (table->completed_meals_count >= table->num_of_philosophers)
			table->is_simulation_running = false;
	}
	kill_all(table);
	sem_post(table->dead_sem);
	return (NULL);
}

void	*personal_reaper(void *philo_ptr)
{
	t_philosopher	*philo;

	philo = (t_philosopher *) philo_ptr;
	wait_delay(philo->table->start_time);
	while (!get_is_dead(philo))
		usleep(100);
	sem_post(philo->simulation_stop_sem);
	return (NULL);
}

void	*personal_listener(void *philo_ptr)
{
	t_philosopher	*philo;

	philo = (t_philosopher *) philo_ptr;
	wait_delay(philo->table->start_time);
	sem_wait(philo->simulation_stop_sem);
	sem_wait(philo->can_print_sem);
	philo->can_write = false;
	sem_post(philo->can_print_sem);
	sem_wait(philo->state_sem);
	philo->state = is_dead;
	sem_post(philo->state_sem);
	return (NULL);
}