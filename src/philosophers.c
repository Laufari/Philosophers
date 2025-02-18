/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laufarin <laufarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 17:42:08 by laufarin          #+#    #+#             */
/*   Updated: 2025/02/18 16:18:57 by laufarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*philosopher_life(void *arg)
{
	t_philosopher *philosopher = (t_philosopher *)arg;// Convertimos el argumento a t_philosopher *
    
    while (1)// El ciclo infinito de la vida del filósofo
    {
        // Aquí irán las acciones del filósofo.
		printf("%ld Philosopher %d is thinking\n", get_time(), philosopher->id);
		usleep(philosopher->resources->time_to_sleep * 1000);//time_to_sleep esta en milisegundo y usleep en microsegundos por eso mult. x 1000
    }
}
