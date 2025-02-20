/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laufarin <laufarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 15:54:24 by laufarin          #+#    #+#             */
/*   Updated: 2025/02/20 17:25:52 by laufarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"
int main(int argc, char **argv)
{
    t_resources resources;
    pthread_t *threads;
    t_philosopher *philos;

    // Primero, valida los argumentos
    if (parse_args(argc, argv))
        return (1);

    // Inicializa los valores en la estructura `resources`
    init(&resources, argv);


    // 🟢 Reservar memoria antes de crear los filósofos
    if (mem_hilos(&threads, &philos, &resources) != 0)
        return (1);

    // 🟢 Crear filósofos y sus hilos
    if (create_philos(&threads, &philos, &resources) != 0)
        return (1);

    // 🟢 Liberar memoria al final
    free_resources(threads, philos);

    return (0);
}

