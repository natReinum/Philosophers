/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmunier <nmunier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 16:42:41 by nmunier           #+#    #+#             */
/*   Updated: 2025/04/11 16:03:20 by nmunier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <my_threads.h>
#include <stdlib.h>

void	free_table(t_table **table)
{
	int	i;

	if (!table || !*table)
		return ;
	if ((*table)->philosophers)
	{
		i = 0;
		while (i < (*table)->num_of_philosophers)
			free_philosopher(&(*table)->philosophers[i++]);
		free((*table)->philosophers);
	}
	if (((*table)->mutexes))
	{
		if ((*table)->mutexes[0])
			(pthread_mutex_destroy((*table)->mutexes[0]), \
				free((*table)->mutexes[0]));
		free((*table)->mutexes);
	}
	if ((*table)->end_simulation_mutex)
		free((*table)->end_simulation_mutex);
	free(*table);
	*table = NULL;
}

static pthread_mutex_t	**create_mutexes(void)
{
	pthread_mutex_t	**mutexes;

	mutexes = malloc(sizeof(pthread_mutex_t *));
	if (!mutexes)
		return (NULL);
	mutexes[0] = malloc(sizeof(pthread_mutex_t));
	if (!mutexes[0])
		return (free(mutexes), NULL);
	if (pthread_mutex_init(mutexes[0], NULL) != 0)
		return (free(mutexes[0]), free(mutexes), NULL);
	return (mutexes);
}

static t_boolean	init_philosophers(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->num_of_philosophers)
	{
		table->philosophers[i] = new_philosopher(i, table->mutexes, table);
		if (!table->philosophers[i++])
			return (false);
	}
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
	table->mutexes = create_mutexes();
	if (!table->mutexes)
		return (free_table(&table), NULL);
	table->time_to_die = times[0];
	table->time_to_eat = times[1];
	table->time_to_sleep = times[2];
	table->num_of_philosophers = philosophers_count;
	table->nb_meals_to_eat = meals_max;
	table->start_time = get_timestamp();
	table->end_simulation_mutex = malloc(sizeof(pthread_mutex_t));
	if (!init_philosophers(table))
		return (free_table(&table), NULL);
	table->is_simulation_running = true;
	return (table);
}

t_boolean	create_threads(t_table *table)
{
	int	i;

	if (pthread_mutex_init(table->end_simulation_mutex, NULL) != 0)
		return (false);
	i = 0;
	while (i < table->num_of_philosophers)
	{
		if (pthread_create(&table->philosophers[i]->thread, NULL,
				routine_philo, table->philosophers[i]) != 0)
			return (false);
		i++;
	}
	if (table->num_of_philosophers > 1)
	{
		if (pthread_create(&table->reaper_thread, NULL, \
			routine_reaper, table) != 0)
			return (false);
	}
	return (true);
}
