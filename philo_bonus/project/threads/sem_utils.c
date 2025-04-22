/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sem_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmunier <nmunier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 18:04:36 by nmunier           #+#    #+#             */
/*   Updated: 2025/04/18 20:56:41 by nmunier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <my_threads.h>

static int	ft_strlen(char *str)
{
	char	*base;

	base = str;
	while (*str)
		str++;
	return (str - base);
}

static char	*get_sem_name(char *str, int id)
{
	int		i;
	char	*str_id;
	char	*str_name;

	str_id = ft_itoa(id);
	str_name = malloc((ft_strlen(str) + ft_strlen(str_id) + 1) * sizeof(char));
	i = -1;
	while (str[++i])
		str_name[i] = str[i];
	i = -1;
	while (str_id[++i])
		str_name[i + ft_strlen(str)] = str_id[i];
	free(str_id);
	str_name[i + ft_strlen(str)] = '\0';
	return (str_name);
}

t_boolean	assign_sem(sem_t **sem, int id, char *str)
{
	char	*sem_name;

	sem_name = get_sem_name(str, id);
	sem_unlink(sem_name);
	*sem = sem_open(sem_name, O_CREAT, SEM_RIGHTS, 1);
	free(sem_name);
	if (*sem == SEM_FAILED)
		return (false);
	return (true);
}

void	unassign_sem(sem_t *sem, int id, char *str)
{
	char	*sem_name;

	sem_name = get_sem_name(str, id);
	sem_close(sem);
	sem_unlink(sem_name);
	free(sem_name);
}

void	unlink_sem(void)
{
	sem_unlink(DEAD_SEMAPHORE);
	sem_unlink(STOP_SEMAPHORE);
	sem_unlink(FORKS_SEMAPHORE);
	sem_unlink(MEALS_SEMAPHORE);
	sem_unlink(PRINTF_SEMAPHORE);
}
