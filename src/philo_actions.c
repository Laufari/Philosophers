/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laufarin <laufarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 13:43:40 by laufarin          #+#    #+#             */
/*   Updated: 2025/03/31 16:25:00 by laufarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "philo.h" 

void take_forks(t_philosopher *philosopher)
{
    // Intentar tomar los tenedores
    if (philosopher->id % 2 == 0)
    {
        pthread_mutex_lock(philosopher->left_fork);
        print_status(philosopher, "has taken left fork");
        pthread_mutex_lock(philosopher->right_fork);
        print_status(philosopher, "has taken right fork");
    }
    else
    {
        pthread_mutex_lock(philosopher->right_fork);
        print_status(philosopher, "has taken right fork");
        pthread_mutex_lock(philosopher->left_fork);
        print_status(philosopher, "has taken left fork");
    }
}

int eat(t_philosopher *philosopher)
{
    pthread_mutex_lock(&philosopher->meal_mutex);
    philosopher->last_meal_time = get_time();
    pthread_mutex_unlock(&philosopher->meal_mutex);
    precise_usleep(philosopher->resources->time_to_eat);  
    print_status(philosopher, "is eating");
    philosopher->times_eaten++;
    if(philosopher->times_eaten >= philosopher->resources->eat_count)
    {
        //printf("finished eating Philo: %i\n", philosopher->id);
        philosopher->resources->num_philos_full++;
        return (1);
    }
    return (0);
}

void put_down_forks(t_philosopher *philosopher)
{
    // Soltar los tenedores
    pthread_mutex_unlock(philosopher->left_fork);
    pthread_mutex_unlock(philosopher->right_fork);
   // print_status(philosopher, "Soltar tenedores");
}
void think(t_philosopher *philosopher)
{
    // Pensar
    print_status(philosopher, "is thinking");
}
void sleep_philosopher(t_philosopher *philosopher)
{
    // Dormir
    print_status(philosopher, "is sleeping");
    precise_usleep(philosopher->resources->time_to_sleep); // Convertir a microsegundos
}
