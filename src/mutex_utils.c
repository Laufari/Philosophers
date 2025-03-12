/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laufarin <laufarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 16:30:28 by laufarin          #+#    #+#             */
/*   Updated: 2025/03/12 19:24:24 by laufarin         ###   ########.fr       */
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
    return(0);
}

void print_status(t_philosopher *philosopher, char *message)
{
    // printf("prueba dead = %i\n", philosopher->resources->is_dead);
    pthread_mutex_lock(&philosopher->resources->print_mutex);
    if (philosopher->resources->is_dead == 0)
        printf("%ld Philosopher %d %s\n", get_time(), philosopher->id, message);
    pthread_mutex_unlock(&philosopher->resources->print_mutex);
}


    //init monitoring
    /*int monitor_philosopher(t_philosopher *philo, t_resources *resources)
    {
        long current_time = get_time();


        pthread_mutex_lock(&resources->mutex);  // Bloquear el mutex para acceder de manera segura
        // while (i < resources->number_of_philosophers)
        // {
            t_philosopher *philosopher = philo;  // Acceder al filósofo actual

        if (philosopher->resources->is_dead)
            return (pthread_mutex_unlock(&resources->mutex),1);
        // Verificar si el filósofo ha muerto
           // printf("HOLAAAAA id: %d lasmeal: %ld currtime: %ld\n", philosopher->id, philosopher->last_meal_time, current_time );
            if (current_time - philosopher->last_meal_time > philosopher->resources->time_to_die)
            {
                if(!philosopher->resources->is_dead)
                    printf("%ld Philosopher %d died for time\n", current_time, philosopher->id);
                // printf("Current time: %ld, Philosopher %d, Last meal: %ld, Time to die: %ld\n", current_time, philosopher->id, philosopher->last_meal_time, philosopher->resources->time_to_die);
                // printf("Current timedos: %ld, Philosopher %d, Last meal: %ld, Time to die: %ld\n", current_time, philosopher->id, philosopher->last_meal_time, philosopher->resources->time_to_die);
                philosopher->resources->is_dead = 1; 
                pthread_mutex_unlock(&resources->mutex);  // Desbloquear el mutex antes de salir
                return 1;  // Retornar 1 si el filósofo ha muerto
             }

        // Verificar si el filósofo ha comido lo suficiente
             if (philosopher->times_eaten != -1 && philosopher->times_eaten >= resources->eat_count)
             {
               printf("%ld Philosopher %d finished eating\n", current_time, philosopher->id);
                printf("Current timetres: %ld, Philosopher %d, Last meal: %ld, Time to die: %ld\n", current_time, philosopher->id, philosopher->last_meal_time, philosopher->resources->time_to_die);

               pthread_mutex_unlock(&resources->mutex);  // Desbloquear el mutex antes de salir
              return 1;  // Retornar 1 si el filósofo ha comido lo suficiente
            }

            // i++;  // Continuar con el siguiente filósofo
       // }
    pthread_mutex_unlock(&resources->mutex);  // Desbloquear el mutex
    //return 0;  // Retornar 0 si ningún filósofo ha muerto o terminado de comer
    return (0);  // Todo salió bien
    }*/
