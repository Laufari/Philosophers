/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laufarin <laufarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 15:20:09 by laufarin          #+#    #+#             */
/*   Updated: 2025/05/22 15:39:00 by laufarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*handle_single_philosopher(void *arg)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)arg;
	pthread_mutex_lock(philo->left_fork);
	print_status(philo, "has taken a fork");
	precise_usleep(philo->resources->time_to_die);
	pthread_mutex_lock(&philo->resources->mutex);
	philo->resources->is_dead = 1;
	pthread_mutex_unlock(&philo->resources->mutex);
	pthread_mutex_unlock(philo->left_fork);
	return (NULL);
}
