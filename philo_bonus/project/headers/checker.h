/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmunier <nmunier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 17:20:39 by nmunier           #+#    #+#             */
/*   Updated: 2025/04/14 14:14:54 by nmunier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECKER_H
# define CHECKER_H
# include <stdio.h>
# include "../struct/boolean_struct.h"

int			ft_atoi(const char *nptr);
t_boolean	input_checker(int argc, char **argv, int *philo_nb, double *times);

#endif // CHECKER_H
