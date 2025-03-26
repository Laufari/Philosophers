/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laufarin <laufarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 14:40:49 by laufarin          #+#    #+#             */
/*   Updated: 2025/03/18 17:58:35 by laufarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"


void    init_resources(t_resources *resources, char **argv)
{
    resources->number_of_philosophers = ft_atoi(argv[1]);
	resources->time_to_die = ft_atoi(argv[2]);
	resources->time_to_eat = ft_atoi(argv[3]);
	resources->time_to_sleep = ft_atoi(argv[4]);
	resources->is_dead = 0;
	resources->can_eat = 0;
	resources->num_philos_full = 0;
	
	pthread_mutex_init(&resources->mutex, NULL);
	pthread_mutex_init(&resources->start_mutex, NULL); 
	if (argv[5])
		resources->eat_count = ft_atoi(argv[5]);  // Inicializa eat_count si hay un quinto argumento
	else
		resources->eat_count = -1;  // Valor por defecto si no se pasa un quinto argumento
}

int	init_forks(t_resources *resources)
{
	int	i;
	resources->forks = malloc(sizeof(pthread_mutex_t) * resources->number_of_philosophers);
	if(!resources->forks)
	{
		printf("Error allocating memory for forks.\n");
		free(resources->forks);
        return 1;  // Error en la asignación)
	}
	i = 0;
	while(i < resources->number_of_philosophers)
	{
	//	pthread_mutex_init(&resources->forks[i], NULL);
		if(pthread_mutex_init(&resources->forks[i], NULL)!= 0)
		{
		 	printf("Error initializing mutex for fork %d.\n", i);
			return(1);
		}
		i++;
	}
	return(0);
}