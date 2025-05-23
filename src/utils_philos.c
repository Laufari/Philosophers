/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_philos.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laufarin <laufarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 15:07:00 by laufarin          #+#    #+#             */
/*   Updated: 2025/05/23 16:21:03 by laufarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	should_stop_execution(t_philosopher *philo)
{
	int	done;
	int	should_stop;

	pthread_mutex_lock(&philo->resources->mutex);
	should_stop = philo->resources->is_dead;
	pthread_mutex_unlock(&philo->resources->mutex);
	if (should_stop)
		return (1);
	done = (philo->resources->eat_count != -1
			&& philo->times_eaten >= philo->resources->eat_count);
	if (done)
	{
		pthread_mutex_lock(&philo->resources->full_mutex);
		philo->resources->num_philos_full++;
		pthread_mutex_unlock(&philo->resources->full_mutex);
		return (1);
	}
	return (0);
}
