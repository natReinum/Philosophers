/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmunier <nmunier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 15:45:45 by nmunier           #+#    #+#             */
/*   Updated: 2025/04/11 18:24:07 by nmunier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <my_threads.h>
#include <signal.h>

void	free_philosopher(t_philosopher **philosopher)
{
	if (!philosopher || !*philosopher)
		return ;
	if ((*philosopher)->r_fork_mutex)
		(pthread_mutex_destroy((*philosopher)->r_fork_mutex), \
			free((*philosopher)->r_fork_mutex));
	if ((*philosopher)->l_fork_mutex)
		(pthread_mutex_destroy((*philosopher)->l_fork_mutex), \
			free((*philosopher)->l_fork_mutex));
	if ((*philosopher)->state_mutex)
		(pthread_mutex_destroy((*philosopher)->state_mutex), \
			free((*philosopher)->state_mutex));
	if ((*philosopher)->last_meal_time_mutex)
		(pthread_mutex_destroy((*philosopher)->last_meal_time_mutex), \
			free((*philosopher)->last_meal_time_mutex));
	if ((*philosopher)->meal_count_mutex)
		(pthread_mutex_destroy((*philosopher)->meal_count_mutex), \
			free((*philosopher)->meal_count_mutex));
	free(*philosopher);
	*philosopher = NULL;
}

static void	init_self(t_philosopher *philosopher)
{
	philosopher->r_fork_mutex = malloc(sizeof(pthread_mutex_t));
	philosopher->meal_count_mutex = malloc(sizeof(pthread_mutex_t));
	philosopher->state_mutex = malloc(sizeof(pthread_mutex_t));
	philosopher->last_meal_time_mutex = malloc(sizeof(pthread_mutex_t));
	if (pthread_mutex_init(philosopher->r_fork_mutex, NULL) != 0)
		return (free_philosopher(&philosopher));
	if (pthread_mutex_init(philosopher->state_mutex, NULL) != 0)
		return (free_philosopher(&philosopher));
	if (pthread_mutex_init(philosopher->last_meal_time_mutex, NULL) != 0)
		return (free_philosopher(&philosopher));
	if (pthread_mutex_init(philosopher->meal_count_mutex, NULL) != 0)
		return (free_philosopher(&philosopher));
	philosopher->last_state = is_thinking;
	if (philosopher->id % 2 == 0)
		philosopher->state = is_thinking;
	else
		philosopher->state = is_eating;
}

t_philosopher	*new_philosopher(const int id, pthread_mutex_t **mutexes, \
								t_table *table)
{
	t_philosopher	*philosopher;

	philosopher = malloc(sizeof(t_philosopher));
	if (!philosopher)
		return (NULL);
	philosopher->id = id + 1;
	philosopher->printf_mutex = mutexes[0];
	philosopher->r_fork_mutex = NULL;
	philosopher->l_fork_mutex = NULL;
	philosopher->meal_count_mutex = NULL;
	philosopher->state_mutex = NULL;
	philosopher->last_meal_time_mutex = NULL;
	philosopher->meal_count = 0;
	philosopher->table = table;
	philosopher->last_meal_time = get_timestamp();
	init_self(philosopher);
	return (philosopher);
}

void	init_neighbors(t_philosopher **philosopher_array, int num_philosophers)
{
	int	i;

	if (!philosopher_array || num_philosophers <= 0)
		return ;
	i = 0;
	while (i < num_philosophers)
	{
		philosopher_array[i]->next_philosopher = philosopher_array[(i + 1) \
			% num_philosophers];
		philosopher_array[i]->prev_philosopher = philosopher_array[(i - 1 \
			+ num_philosophers) % num_philosophers];
		i++;
	}
}
