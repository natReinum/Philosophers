/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmunier <nmunier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 15:45:45 by nmunier           #+#    #+#             */
/*   Updated: 2025/04/22 16:51:07 by nmunier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <my_threads.h>

void	free_philosopher(t_philosopher **philosopher)
{
	if (!philosopher || !*philosopher)
		return ;
	unassign_sem((*philosopher)->state_sem, (*philosopher)->id, \
		LOCAL_STATE_SEMAPHORE);
	unassign_sem((*philosopher)->is_dead_sem, (*philosopher)->id, \
		LOCAL_DEAD_SEMAPHORE);
	unassign_sem((*philosopher)->can_print_sem, (*philosopher)->id, \
		LOCAL_WRITE_SEMAPHORE);
	free(*philosopher);
	*philosopher = NULL;
}

static t_boolean	init_self(t_philosopher *philosopher)
{
	if (philosopher->id % 2 == 0)
		philosopher->state = is_thinking;
	else
		philosopher->state = is_eating;
	philosopher->printf_sem = philosopher->table->printf_sem;
	philosopher->has_eaten_sem = philosopher->table->completed_meals_sem;
	philosopher->forks_sem = philosopher->table->forks_sem;
	philosopher->simulation_stop_sem = philosopher->table->simulation_stop_sem;
	if (!assign_sem(&philosopher->state_sem, philosopher->id, \
		LOCAL_STATE_SEMAPHORE))
		return (false);
	if (!assign_sem(&philosopher->is_dead_sem, philosopher->id, \
		LOCAL_DEAD_SEMAPHORE))
		return (false);
	if (!assign_sem(&philosopher->can_print_sem, philosopher->id, \
		LOCAL_WRITE_SEMAPHORE))
		return (false);
	return (true);
}

t_philosopher	*new_philosopher(const int id, t_table *table)
{
	t_philosopher	*philosopher;

	philosopher = malloc(sizeof(t_philosopher));
	if (!philosopher)
		return (NULL);
	philosopher->id = id + 1;
	philosopher->meal_count = 0;
	philosopher->fork_count = 0;
	philosopher->table = table;
	philosopher->is_dead = false;
	philosopher->can_write = true;
	philosopher->last_meal_time = get_timestamp();
	init_self(philosopher);
	sem_wait(philosopher->table->dead_sem);
	sem_wait(philosopher->has_eaten_sem);
	return (philosopher);
}
