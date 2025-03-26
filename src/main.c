/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laufarin <laufarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 15:54:24 by laufarin          #+#    #+#             */
/*   Updated: 2025/03/26 16:33:18 by laufarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int main(int argc, char **argv)
{
    t_resources resources;
    pthread_t *threads;
    int i;

    if (parse_args(argc, argv)) // Validar argumentos
        return (1);

    init_resources(&resources, argv);
    init_forks(&resources);
    i = 0;
    if (mem_hilos(&threads, &resources)) // Reservar memoria
        return (1);
    if (create_philos(&threads, &resources)) // Crear hilos de filósofos
        return (1);
    resources.can_eat = 1;
    resources.time_init = get_time();   
    // 🟢 Monitorear filósofos
    monitor_philosophers(&resources);
        i = 0;
        while (i < resources.number_of_philosophers)
        {
            pthread_join(threads[i], NULL);
            i++;
        }
    free_resources(threads, &resources); // 🟢 Liberar memoria al final
    return (0);
}

