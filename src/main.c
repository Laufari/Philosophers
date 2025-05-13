/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laufarin <laufarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 15:54:24 by laufarin          #+#    #+#             */
/*   Updated: 2025/05/13 15:57:25 by laufarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int	init_all(t_resources *resources, pthread_t **threads)
{
	if (init_forks(resources) || init_printmutex(resources))
	{
		printf("Error initializing forks or print mutex.\n");
		return (1);
	}
	if (mem_hilos(threads, resources))
	{
		printf("Error allocating memory for threads or philosophers.\n");
		return (1);
	}
	return (0);
}

static int	start_simulation(t_resources *resources, pthread_t *threads)
{
	pthread_mutex_lock(&resources->mutex);
	resources->can_eat = 1;
	resources->time_init = get_time();
	pthread_mutex_unlock(&resources->mutex);
	if (create_philos(&threads, resources))
	{
		printf("Error creating philosopher threads.\n");
		return (1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_resources	resources;
	pthread_t	*threads;
	int			i;

	i = 0;
	if (parse_args(argc, argv))
		return (1);
	init_resources(&resources, argv);
	if (init_all(&resources, &threads))
		return (1);
	if (start_simulation(&resources, threads))
		return (1);
	if (monitor_philosophers(&resources))
		printf("A philosopher has died.\n");
	else
		printf("All philosophers have eaten enough.\n");
	while (i < resources.number_of_philosophers)
		pthread_join(threads[i++], NULL);
	free_resources(threads, &resources);
	return (0);
}
