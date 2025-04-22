/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmunier <nmunier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 16:32:38 by nmunier           #+#    #+#             */
/*   Updated: 2025/04/22 16:55:20 by nmunier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <process.h>

void	child_process(t_philosopher *philosopher)
{
	if (pthread_create(&philosopher->personal_reaper, NULL, \
		personal_reaper, philosopher) != 0)
		return ;
	if (pthread_create(&philosopher->stop_sim_thread, NULL, \
		personal_listener, philosopher))
		return ;
	routine_philo(philosopher);
}

void	exit_child(t_philosopher *philo)
{
	t_table	*table;

	table = philo->table;
	sem_wait(philo->printf_sem);
	printf(DIED_MSG, get_local_time(table), philo->id);
	sem_post(philo->simulation_stop_sem);
	sem_post(philo->table->dead_sem);
	sem_post(philo->forks_sem);
	pthread_join(philo->personal_reaper, NULL);
	pthread_join(philo->stop_sim_thread, NULL);
	free_table(&table);
	exit(0);
}
