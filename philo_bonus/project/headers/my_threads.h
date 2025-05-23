/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_threads.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmunier <nmunier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 15:46:16 by nmunier           #+#    #+#             */
/*   Updated: 2025/04/22 17:38:31 by nmunier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MY_THREADS_H
# define MY_THREADS_H
# include <stdio.h>
# include <fcntl.h>
# include <signal.h>
# include <stddef.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include "../struct/philosopher_struct.h"

t_philosopher	*new_philosopher(int idu, t_table *table);
void			free_philosopher(t_philosopher **philosopher);

t_table			*create_table(int philosophers_count, double *times, \
					int meals_max);
void			free_table(t_table **table);

void			*routine_philo(t_philosopher *philo);
void			*routine_first_reaper(void *table_ptr);
void			*routine_third_reaper(void *table_ptr);
void			*personal_reaper(void *philo_ptr);
void			*personal_listener(void *philo_ptr);
void			child_process(t_philosopher *philosophers);

void			think(t_philosopher *philo);
void			eat(t_philosopher *philo);
void			rest(t_philosopher *philo);
void			change_state(t_philosopher *philo, t_state new_state);
t_state			get_state(t_philosopher *philo);

t_boolean		grab_fork(t_philosopher *philo);
t_boolean		release_fork(t_philosopher *philo);

t_boolean		get_is_dead(t_philosopher *philo);
t_boolean		get_has_eaten(t_philosopher *philo);
t_boolean		check_end_condition(t_table *table);
t_boolean		reap(t_table *table);
t_boolean		has_simulation_ended(t_table *table);

void			printf_philosopher(t_philosopher *philosopher, \
					char *str, t_table *table);
t_boolean		can_print(t_philosopher *philo);

t_boolean		assign_sem(sem_t **sem, int id, char *str);
void			unassign_sem(sem_t *sem, int id, char *str);
void			unlink_sem(void);

void			ft_sleep(time_t mili_s, t_philosopher *philosopher);
time_t			get_timestamp(void);
time_t			get_local_time(t_table *table);
time_t			min(time_t a, time_t b);
void			wait_delay(time_t delay);

void			exit_child(t_philosopher *philo);
void			kill_all(t_table *table);

char			*ft_itoa(int n);

#endif // MY_THREADS_H
