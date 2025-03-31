/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laufarin <laufarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 15:19:08 by laufarin          #+#    #+#             */
/*   Updated: 2025/03/31 17:43:55 by laufarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int mem_hilos(pthread_t **threads, t_resources *resources)
{
    int i;

    i = 0;
    *threads = malloc(sizeof(pthread_t) * resources->number_of_philosophers);
    resources->philos = malloc(sizeof(t_philosopher) * resources->number_of_philosophers);
    if(!(*threads) || !(resources->philos) || !(resources->forks))
    {
        printf("Error allocating memory for philosophers or threads.\n");
        free_resources(*threads, resources);
        return (1);
    }
    while(i < resources->number_of_philosophers)
    {
        pthread_mutex_init(&resources->forks[i], NULL);
        // Inicializamos los punteros de los filósofos a los tenedores
        (resources->philos)[i].left_fork = &resources->forks[i];  // Tenedor izquierdo
        (resources->philos)[i].right_fork = &resources->forks[(i + 1) % resources->number_of_philosophers];  // Tenedor derecho
        i++;
    }
    return(0);
}

static int init_philos(t_resources *resources)
{
    int i;

    i = 0;
    while (i < resources->number_of_philosophers)
    {
        resources->philos[i].id = i + 1;
        resources->philos[i].resources = resources;
        resources->philos[i].last_meal_time = get_time();
        resources->philos[i].times_eaten = 0;
        if (pthread_mutex_init(&(resources->philos[i].meal_mutex), NULL) != 0)
        {
            while (i > 0)
            {
                i--;
                pthread_mutex_destroy(&(resources->philos[i].meal_mutex));
            }
            return (1);
        }
        i++;
    }
    return (0);
}

static int start_philos_threads(pthread_t **threads, t_resources *resources)
{
    int i;

    i = 0;
    while (i < resources->number_of_philosophers)
    {
        if (pthread_create(&(*threads)[i], NULL, philosopher_life, (void *)&(resources->philos[i])) != 0)
        {
            while (i > 0)
            {
                i--;
                pthread_mutex_destroy(&(resources->philos[i].meal_mutex));
            }
            return (1);
        }
        i++;
    }
    return (0);
}

int create_philos(pthread_t **threads, t_resources *resources)
{
    if (init_philos(resources) != 0)
        return (1);
    if (start_philos_threads(threads, resources) != 0)
        return (1);
    return (0);
}


/*int create_philos(pthread_t **threads, t_resources *resources)
{
    int i;
    
    i = 0;
    while (i < resources->number_of_philosophers) // Creamos filósofos y asignamos propiedades
    {
        resources->philos[i].id = i + 1;
        resources->philos[i].resources = resources;
        resources->philos[i].last_meal_time = get_time();  // Inicializa el tiempo de la última comida
        resources->philos[i].times_eaten = 0;  // Asegurar que empiece en 0
        if (pthread_mutex_init(&(resources->philos[i].meal_mutex), NULL) != 0)
        {
            while (i > 0)
            {
                i--;
                pthread_mutex_destroy(&(resources->philos[i].meal_mutex));
            }
            return (1);
        }
        // Crear el hilo del filósofo
        if (pthread_create(&(*threads)[i], NULL, philosopher_life, (void *)&(resources->philos)[i]) != 0)
        {
            while (i > 0)
            {
                i--;
                pthread_mutex_destroy(&(resources->philos[i].meal_mutex));
            }
            return (1);
        }
        i++;
    }
    return (0);
}*/
