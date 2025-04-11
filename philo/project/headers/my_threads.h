/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_threads.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmunier <nmunier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 15:46:16 by nmunier           #+#    #+#             */
/*   Updated: 2025/04/11 20:10:31 by nmunier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MY_THREADS_H
# define MY_THREADS_H
# include <stddef.h>
# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include "../struct/philosopher_struct.h"

t_philosopher	*new_philosopher(int id, pthread_mutex_t **mutexes, \
								t_table *table);
void			free_philosopher(t_philosopher **philosopher);
void			init_neighbors(t_philosopher **philosopher_array, \
								int num_philosophers);
void			printf_philosopher(t_philosopher *philosopher, char *str, \
								t_table *table);

t_table			*create_table(int hilosophers_count, double *times, \
								int meals_max);
void			free_table(t_table **table);

void			*routine_philo(void *philosopher);
void			*routine_reaper(void *table_ptr);
t_boolean		reap(t_table *table);
t_boolean		create_threads(t_table *table);

void			ft_sleep(time_t mili_s, t_table *table);
time_t			get_timestamp(void);
time_t			get_local_time(t_table *table);
time_t			min(time_t a, time_t b);

void			think(t_philosopher *philo);
void			eat(t_philosopher *philo);
void			rest(t_philosopher *philo);
void			change_state(t_philosopher *philo, t_state new_state);
t_state			get_state(t_philosopher *philo);

t_boolean		grab_fork(t_philosopher *philo);
t_boolean		release_fork(t_philosopher *philo);

t_boolean		get_is_dead(t_philosopher *philo);
t_boolean		get_has_eaten(t_philosopher *philo);
t_boolean		has_simulation_ended(t_table *table);
t_boolean		check_end_condition(t_table *table);

#endif // MY_THREADS_H
