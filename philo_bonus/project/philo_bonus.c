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

t_boolean	create_threads(t_table *table)
{
	if (pthread_create(&table->reaper_first_thread, NULL, \
		routine_first_reaper, table) != 0)
		return (false);
	if (pthread_create(&table->reaper_third_thread, NULL, \
		routine_third_reaper, table) != 0)
		return (false);
	return (true);
}

t_boolean	create_processes(t_table *table)
{
	int		i;
	pid_t	pid;

	i = -1;
	while (++i < table->num_of_philosophers)
	{
		pid = fork();
		if (pid == -1)
			return (false);
		if (pid > 0)
			table->pids_philo[i] = pid;
		else
			child_process(table->philosophers[i]);
	}
	create_threads(table);
	return (true);
}

int	main(int argc, char **argv)
{
	int		philo_nb;
	double	times[4];
	t_table	*table;

	if (!input_checker(argc, argv, &philo_nb, times))
		return (-42);
	table = create_table(philo_nb, times, times[3]);
	create_processes(table);
	waitpid(-1, NULL, 0);
	kill_all(table);
	pthread_join(table->reaper_first_thread, NULL);
	pthread_join(table->reaper_third_thread, NULL);
	free_table(&table);
	unlink_sem();
	return (0);
}