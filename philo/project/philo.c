/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmunier <nmunier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 14:01:51 by nmunier           #+#    #+#             */
/*   Updated: 2025/04/11 19:28:44 by nmunier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	join_threads(t_table *table)
{
	int		i;

	i = 0;
	while (i < table->num_of_philosophers)
	{
		pthread_join(table->philosophers[i]->thread, NULL);
		i++;
	}
	if (table->num_of_philosophers > 1)
		pthread_join(table->reaper_thread, NULL);
}

int	main(int argc, char **argv)
{
	int		philo_nb;
	double	times[4];
	t_table	*table;

	if (!input_checker(argc, argv, &philo_nb, times))
		return (-42);
	table = create_table(philo_nb, times, times[3]);
	init_neighbors(table->philosophers, philo_nb);
	if (!create_threads(table))
		return (free_table(&table), -42);
	join_threads(table);
	free_table(&table);
	return (0);
}
