/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmunier <nmunier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 17:47:32 by nmunier           #+#    #+#             */
/*   Updated: 2025/04/18 15:08:59 by nmunier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <my_threads.h>

t_boolean	check_end_condition(t_table *table)
{
	int	i;
	int	alive_philo;

	i = 0;
	alive_philo = 0;
	while (i < table->num_of_philosophers)
	{
		if (!get_is_dead(table->philosophers[i]) \
			&& !get_has_eaten(table->philosophers[i]))
			alive_philo++;
		i++;
	}
	if (alive_philo < table->num_of_philosophers)
		return (true);
	return (false);
}

t_boolean	reap(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->num_of_philosophers)
	{
		if (get_local_time(table) - table->philosophers[i]->last_meal_time \
			>= table->time_to_die)
		{
			change_state(table->philosophers[i], is_dead);
			printf_philosopher(table->philosophers[i], DIED_MSG, table);
			return (true);
		}
		i++;
	}
	return (false);
}
