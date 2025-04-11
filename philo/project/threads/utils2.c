/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmunier <nmunier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 15:26:47 by nmunier           #+#    #+#             */
/*   Updated: 2025/04/04 15:29:36 by nmunier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <my_threads.h>

t_boolean	get_is_dead(t_philosopher *philo)
{
	t_boolean	value;

	value = false;
	pthread_mutex_lock(philo->state_mutex);
	if (philo->state == is_dead)
		value = true;
	pthread_mutex_unlock(philo->state_mutex);
	return (value);
}
