/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laufarin <laufarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 17:42:08 by laufarin          #+#    #+#             */
/*   Updated: 2025/03/31 16:00:56 by laufarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void *philosopher_life(void *arg)
{
    t_philosopher *philosopher;

    philosopher = (t_philosopher *)arg;
    while (philosopher->resources->is_dead == 0)
    {

        if (!philosopher->resources->can_eat)
        {
                precise_usleep(1);
                continue ;
        }
        if (philosopher->id % 2 == 0)
        {
            precise_usleep(2); // Pausa inicial para evitar colisiones
        }
        if (philosopher->resources->is_dead == 1)
        {
            return (NULL);
        }
       // pthread_mutex_unlock(&philosopher->resources->mutex);
        take_forks(philosopher);    // Tomar los tenedores
        if (eat(philosopher))
        {
            put_down_forks(philosopher); // 🔥 Asegurar que libere los tenedores
            break ;
        }          // Comer
        put_down_forks(philosopher); // Soltar los tenedores
        sleep_philosopher(philosopher); // Dormir
        think(philosopher);         // Pensar
    }
    return (NULL);
}

int monitor_philosophers(t_resources *resources)
{
    long current_time;
    int i;
    long last_meal;

    i = 0;
    last_meal = -1;
    current_time = get_time();
    
    pthread_mutex_lock(&resources->mutex);
    while(!resources->is_dead)
    {
        pthread_mutex_unlock(&resources->mutex);
        i = 0;
        while (i < resources->number_of_philosophers)
        {   
            pthread_mutex_lock(&resources->philos->meal_mutex); // Bloquea el acceso
            current_time = get_time();
            last_meal = resources->philos[i].last_meal_time;
            if (current_time - last_meal > resources->time_to_die)
            {
               // printf("entraaa \n");
                //printf("Philosopher %i cur time %li last meal %ld, time to die %ld\n", resources->philos->id, current_time, last_meal, resources->time_to_die);
                (*resources).is_dead = 1;
                pthread_mutex_unlock(&resources->mutex);
                
                printf("%ld Philosopher %i died for time\n", current_time - resources->time_init, resources->philos->id);
                return (1);
            }
            pthread_mutex_unlock(&resources->philos->meal_mutex); // Desbloquea después
            //pthread_mutex_lock(&resources->full_mutex);
            if(resources->num_philos_full >= resources->number_of_philosophers)	
            {
                
              //  pthread_mutex_unlock(&resources->full_mutex);
		        return(0);
            }
            //pthread_mutex_unlock(&resources->full_mutex);
            i++;
        }
        precise_usleep(1);
    }
    pthread_mutex_unlock(&resources->mutex);
    return (0);
}