/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laufarin <laufarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 17:42:08 by laufarin          #+#    #+#             */
/*   Updated: 2025/03/12 19:40:30 by laufarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void think(t_philosopher *philosopher)
{
    // Pensar
    print_status(philosopher, "is thinking");
}
void *philosopher_life(void *arg)
{
    t_philosopher *philosopher;

    philosopher = (t_philosopher *)arg;
    
    pthread_mutex_lock(&philosopher->resources->start_mutex);
    while (philosopher->resources->can_eat == 0)
    {
        pthread_mutex_unlock(&philosopher->resources->start_mutex);
        usleep(10);
        pthread_mutex_lock(&philosopher->resources->start_mutex);
    }
    pthread_mutex_unlock(&philosopher->resources->start_mutex);

    pthread_mutex_lock(&philosopher->meal_mutex);
    philosopher->last_meal_time = get_time();  // Inicializa el tiempo de la última comida
    pthread_mutex_unlock(&philosopher->meal_mutex);

    
    if (philosopher->id % 2 == 0)
        usleep(philosopher->resources->time_to_eat * 500); // Pausa inicial para evitar colisiones

    while (1 )// && philosopher->resources->is_dead == 0)
    {
        pthread_mutex_lock(&philosopher->resources->mutex);
        if (philosopher->resources->is_dead == 1 \
                && 0 >= pthread_mutex_unlock(&philosopher->resources->mutex))
            return (NULL);
        pthread_mutex_unlock(&philosopher->resources->mutex);

        //if (!caneat)
           // continue ;
        think(philosopher);         // Pensar
        take_forks(philosopher);    // Tomar los tenedores
        eat(philosopher);           // Comer
        put_down_forks(philosopher); // Soltar los tenedores
        sleep_philosopher(philosopher); // Dormir
    }
    return (NULL);
}

int monitor_philosophers(t_philosopher **philosopher, t_resources *resources)
{
    long current_time;
    int i;
    long last_meal;

    i = 0;
    current_time = get_time();

pthread_mutex_lock(&resources->mutex);
while((*resources).is_dead != 1)
{
    pthread_mutex_unlock(&resources->mutex);

    while (i < resources->number_of_philosophers)
    {   
        current_time = get_time();
        pthread_mutex_lock(&philosopher[i]->meal_mutex); // 🔥 Bloquea el acceso
        last_meal = philosopher[i]->last_meal_time;
        if(last_meal == -1)
        {
            pthread_mutex_unlock(&philosopher[i]->meal_mutex); // 🔥 Desbloquea después
            continue ;
        }
        pthread_mutex_unlock(&philosopher[i]->meal_mutex); // 🔥 Desbloquea después

        pthread_mutex_lock(&resources->mutex);
        if (current_time - last_meal > resources->time_to_die)
        {
            printf("entraaa\n");
            (*resources).is_dead = 1;
            pthread_mutex_unlock(&resources->mutex);
            
            printf("%ld Philosopher %i died for time\n", current_time, philosopher[i]->id);
            return (1);
        }
        pthread_mutex_unlock(&resources->mutex);
        i++;
    }
    usleep(10);
}
pthread_mutex_unlock(&resources->mutex);
    return (0);
}