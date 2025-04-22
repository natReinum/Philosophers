/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_struct.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmunier <nmunier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 14:32:39 by nmunier           #+#    #+#             */
/*   Updated: 2025/04/22 14:31:40 by nmunier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_STRUCT_H
# define PHILOSOPHER_STRUCT_H
# include <stddef.h>
# include <pthread.h>
# include <semaphore.h>
# include "boolean_struct.h"

# define DIED_MSG 		"\033[0;91m%lu %d died\033[0;39m\n"
# define EATING_MSG 	"\033[0;93m%lu %d is eating\033[0;39m\n"
# define SLEEPING_MSG 	"\033[0;94m%lu %d is sleeping\033[0;39m\n"
# define THINKING_MSG 	"\033[0;92m%lu %d is thinking\033[0;39m\n"
# define FORK_TAKEN_MSG "\033[0;96m%lu %d has taken a fork\033[0;39m\n"

# define DEAD_SEMAPHORE        "/global_dead_sem"
# define STOP_SEMAPHORE        "/global_stop_sem"
# define FORKS_SEMAPHORE       "/global_forks_sem"
# define MEALS_SEMAPHORE       "/global_meals_sem"
# define PRINTF_SEMAPHORE      "/global_printf_sem"
# define LOCAL_DEAD_SEMAPHORE  "/local_dead_sem_"
# define LOCAL_STATE_SEMAPHORE "/local_state_sem_"
# define LOCAL_WRITE_SEMAPHORE "/local_write_sem_"
# define SEM_RIGHTS			   0644

typedef enum e_state
{
	is_eating,
	is_thinking,
	is_sleeping,
	is_dead
}				t_state;

typedef struct s_philosopher
{
	int						id;
	pthread_t				personal_reaper;
	pthread_t				stop_sim_thread;
	t_state					state;
	sem_t					*printf_sem;
	sem_t					*forks_sem;
	sem_t					*state_sem;
	sem_t					*has_eaten_sem;
	sem_t					*is_dead_sem;
	sem_t					*simulation_stop_sem;
	sem_t					*can_print_sem;
	unsigned int			last_meal_time;
	t_boolean				is_dead;
	t_boolean				can_write;
	int						meal_count;
	int						fork_count;
	struct s_table			*table;
}				t_philosopher;

typedef struct s_table
{
	t_boolean		is_simulation_running;
	time_t			time_to_die;
	time_t			time_to_eat;
	time_t			time_to_sleep;
	int				num_of_philosophers;
	sem_t			*printf_sem;
	sem_t			*forks_sem;
	sem_t			*completed_meals_sem;
	sem_t			*dead_sem;
	sem_t			*simulation_stop_sem;
	int				completed_meals_count;
	int				nb_meals_to_eat;
	pthread_t		reaper_first_thread;
	pthread_t		reaper_third_thread;
	t_philosopher	*self;
	t_philosopher	**philosophers;
	pid_t			*pids_philo;
	time_t			start_time;
}				t_table;

#endif // PHILOSOPHER_STRUCT_H
