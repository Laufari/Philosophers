/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laufarin <laufarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 15:19:08 by laufarin          #+#    #+#             */
/*   Updated: 2025/03/12 19:16:55 by laufarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int mem_hilos(pthread_t **threads, t_philosopher **philos, t_resources *resources)
{
    int i;

    i = 0;
    *threads = malloc(sizeof(pthread_t) * resources->number_of_philosophers);
    *philos = malloc(sizeof(t_philosopher) * resources->number_of_philosophers);
    resources->forks = malloc(sizeof(pthread_mutex_t) * resources->number_of_philosophers);
    if(!(*threads) || !(*philos) || !(resources->forks))
    {
        printf("Error allocating memory for philosophers or threads.\n");
        free_resources(*threads, *philos, resources);
        return (1);
    }
    while(i < resources->number_of_philosophers)
    {
        pthread_mutex_init(&resources->forks[i], NULL);
        // Inicializamos los punteros de los filósofos a los tenedores
        (*philos)[i].left_fork = &resources->forks[i];  // Tenedor izquierdo
        (*philos)[i].right_fork = &resources->forks[(i + 1) % resources->number_of_philosophers];  // Tenedor derecho
        i++;
    }
    return(0);
}
int create_philos(pthread_t **threads, t_philosopher **philos, t_resources *resources)
{
    int i;
    //long current_time;

    i = 0;
    //current_time = get_time(); // Obtener el tiempo una sola vez

    while (i < resources->number_of_philosophers) // Creamos filósofos y asignamos propiedades
    {
        (*philos)[i].id = i + 1;
        (*philos)[i].resources = resources;
        (*philos)[i].last_meal_time = -1;  // Inicializa el tiempo de la última comida

        //(*philos)[i].last_meal_time = current_time;  // Inicializa el tiempo de la última comida
        (*philos)[i].times_eaten = 0;  // Asegurar que empiece en 0
        pthread_mutex_init(&(*philos)[i].meal_mutex, NULL);

        // Crear el hilo del filósofo
        if (pthread_create(&(*threads)[i], NULL, philosopher_life, (void *)&(*philos)[i]) != 0)
        {
            printf("Error creating thread.\n");
            free_resources(*threads, *philos, resources);
            return (1);
        }
        i++;
    }
	return (0);
}
