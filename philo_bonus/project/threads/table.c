/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmunier <nmunier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 16:42:41 by nmunier           #+#    #+#             */
/*   Updated: 2025/04/22 17:38:36 by nmunier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <my_threads.h>

void	free_table(t_table **table)
{
	int	i;
	int	max;

	if (!table || !*table)
		return ;
	if ((*table)->philosophers)
	{
		i = 0;
		max = (*table)->num_of_philosophers;
		while (i < max)
			free_philosopher(&(*table)->philosophers[i++]);
		free((*table)->philosophers);
		(*table)->philosophers = NULL;
	}
	sem_close((*table)->dead_sem);
	sem_close((*table)->forks_sem);
	sem_close((*table)->completed_meals_sem);
	sem_close((*table)->simulation_stop_sem);
	sem_close((*table)->printf_sem);
	free((*table)->pids_philo);
	(*table)->pids_philo = NULL;
	free(*table);
	*table = NULL;
}

static t_boolean	init_philosophers(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->num_of_philosophers)
	{
		table->philosophers[i] = new_philosopher(i, table);
		if (!table->philosophers[i++])
			return (false);
	}
	return (true);
}

static t_boolean	init_table_sem(t_table *table)
{
	unlink_sem();
	table->dead_sem = sem_open(DEAD_SEMAPHORE, O_CREAT, SEM_RIGHTS, \
								table->num_of_philosophers);
	if (table->dead_sem == SEM_FAILED)
		return (false);
	table->forks_sem = sem_open(FORKS_SEMAPHORE, O_CREAT, SEM_RIGHTS, \
								table->num_of_philosophers);
	if (table->forks_sem == SEM_FAILED)
		return (false);
	table->completed_meals_sem = sem_open(MEALS_SEMAPHORE, O_CREAT, \
								SEM_RIGHTS, table->num_of_philosophers);
	if (table->completed_meals_sem == SEM_FAILED)
		return (false);
	table->simulation_stop_sem = sem_open(STOP_SEMAPHORE, O_CREAT, \
								SEM_RIGHTS, 0);
	if (table->simulation_stop_sem == SEM_FAILED)
		return (false);
	table->printf_sem = sem_open(PRINTF_SEMAPHORE, O_CREAT, SEM_RIGHTS, 1);
	if (table->printf_sem == SEM_FAILED)
		return (false);
	return (true);
}

t_table	*create_table(int philosophers_count, double *times, int meals_max)
{
	t_table	*table;

	table = malloc(sizeof(t_table));
	if (!table)
		return (NULL);
	table->philosophers = malloc(philosophers_count * sizeof(t_philosopher *));
	if (!table->philosophers)
		return (free_table(&table), NULL);
	table->pids_philo = malloc(philosophers_count * sizeof(pid_t));
	if (!table->pids_philo)
		return (free_table(&table), NULL);
	table->time_to_die = times[0];
	table->time_to_eat = times[1];
	table->time_to_sleep = times[2];
	table->num_of_philosophers = philosophers_count;
	table->nb_meals_to_eat = meals_max;
	table->start_time = get_timestamp() + (philosophers_count + 2) * 10;
	if (!init_table_sem(table))
		return (free_table(&table), NULL);
	if (!init_philosophers(table))
		return (free_table(&table), NULL);
	table->is_simulation_running = true;
	return (table);
}
