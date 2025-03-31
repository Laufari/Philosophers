/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_resources.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laufarin <laufarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 16:30:23 by laufarin          #+#    #+#             */
/*   Updated: 2025/03/31 17:43:13 by laufarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	free_resources(pthread_t *threads, t_resources *resources)
{
	int	i;

	if (threads)
		free(threads);
	if (resources->forks)
	{
		i = 0;
		while (i < resources->number_of_philosophers)
		{
			pthread_mutex_destroy(&resources->forks[i]);
			i++;
		}
		free(resources->forks);
	}
	if (resources->philos)
	{
		i = 0;
		while (i < resources->number_of_philosophers)
		{
			pthread_mutex_destroy(&resources->philos[i].meal_mutex);
			i++;
		}
		free(resources->philos);
	}
	pthread_mutex_destroy(&resources->print_mutex);
	pthread_mutex_destroy(&resources->mutex);
	pthread_mutex_destroy(&resources->start_mutex);
	//pthread_mutex_destroy(&resources->full_mutex);
}
