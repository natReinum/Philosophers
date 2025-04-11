/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_struct.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmunier <nmunier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 14:32:39 by nmunier           #+#    #+#             */
/*   Updated: 2025/04/11 18:07:43 by nmunier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_STRUCT_H
# define PHILOSOPHER_STRUCT_H
# include <pthread.h>
# include <stddef.h>
# include "boolean_struct.h"

# define FORK_TAKEN_MSG "\033[0;96m%lu %d has taken a fork\033[0;39m\n"
# define EATING_MSG 	"\033[0;93m%lu %d is eating\033[0;39m\n"
# define SLEEPING_MSG 	"\033[0;94m%lu %d is sleeping\033[0;39m\n"
# define THINKING_MSG 	"\033[0;92m%lu %d is thinking\033[0;39m\n"
# define DIED_MSG 		"\033[0;91m%lu %d died\033[0;39m\n"

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
	pthread_t				thread;
	t_state					state;
	t_state					last_state;
	pthread_mutex_t			*printf_mutex;
	pthread_mutex_t			*r_fork_mutex;
	pthread_mutex_t			*last_meal_time_mutex;
	pthread_mutex_t			*meal_count_mutex;
	pthread_mutex_t			*state_mutex;
	unsigned int			last_meal_time;
	int						meal_count;
	struct s_table			*table;
	struct s_philosopher	*next_philosopher;
	struct s_philosopher	*prev_philosopher;
}				t_philosopher;

typedef struct s_table
{
	t_boolean		is_simulation_running;
	time_t			time_to_die;
	time_t			time_to_eat;
	time_t			time_to_sleep;
	int				num_of_philosophers;
	int				nb_meals_to_eat;
	pthread_t		reaper_thread;
	t_philosopher	**philosophers;
	pthread_mutex_t	**mutexes;
	pthread_mutex_t	*end_simulation_mutex;
	time_t			start_time;
}				t_table;

#endif // PHILOSOPHER_STRUCT_H
