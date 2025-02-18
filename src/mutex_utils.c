/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laufarin <laufarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 16:30:28 by laufarin          #+#    #+#             */
/*   Updated: 2025/02/18 16:18:55 by laufarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int init_mutexes(t_resources *resources)
{
    int i;
// Inicializar el mutex de impresión
    if (pthread_mutex_init(&resources->print_mutex, NULL) != 0)
    {
        printf("Error: Failed to initialize print mutex.\n");
        return (1);
    }
    // Asignar memoria para los mutexes de los tenedores
    resources->forks = malloc(sizeof(pthread_mutex_t) * resources->number_of_philosophers);
    if (!resources->forks)
    {
        printf("Error: Failed to allocate memory for forks.\n");
        return (1);
    }
    // Inicializar cada mutex de tenedor
    i = 0;
    while (i < resources->number_of_philosophers)
    {
        if (pthread_mutex_init(&resources->forks[i], NULL) != 0)
        {
            printf("Error: Failed to initialize fork mutex %d.\n", i);
            return (1);
        }
        i++;
    }
    //init monitoring
    return (0);  // Todo salió bien
}
