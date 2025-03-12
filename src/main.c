/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laufarin <laufarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 15:54:24 by laufarin          #+#    #+#             */
/*   Updated: 2025/03/12 19:22:01 by laufarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int main(int argc, char **argv)
{
    t_resources resources;
    pthread_t *threads;
    t_philosopher *philos;
    int i;

    if (parse_args(argc, argv)) // Validar argumentos
        return (1);

    init_resources(&resources, argv);
    init_forks(&resources);

    if (mem_hilos(&threads, &philos, &resources) != 0) // Reservar memoria
        return (1);
    if (create_philos(&threads, &philos, &resources) != 0) // Crear hilos de filósofos
        return (1);
    pthread_mutex_lock(&resources.start_mutex);
    resources.can_eat = 1;
    pthread_mutex_unlock(&resources.start_mutex);   
    // 🟢 Monitorear filósofos
    monitor_philosophers(&philos, &resources);
        i = 0;
        while (i < resources.number_of_philosophers)
        {
            //printf("test thread[%i]\n",i);
            pthread_join(threads[i], NULL);
            i++;
        }
    free_resources(threads, philos, &resources); // 🟢 Liberar memoria al final
    return (0);
}

