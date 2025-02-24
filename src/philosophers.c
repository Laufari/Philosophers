/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laufarin <laufarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 17:42:08 by laufarin          #+#    #+#             */
/*   Updated: 2025/02/24 22:18:46 by laufarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*philosopher_life(void *arg)
{
	t_philosopher *philosopher = (t_philosopher *)arg;// Convertimos el argumento a t_philosopher *
    
    while (1)// El ciclo infinito de la vida del filósofo
    {
     //REVISAR ESTO FALTA MODIFICAR PARA PODER PASARLE eat_count 
   //  if (monitor_philosopher(philosopher,)) // Verifica si murió
    //        return NULL;

		  printf("%ld Philosopher %d is thinking\n", get_time(), philosopher->id);
		  usleep(philosopher->resources->time_to_sleep * 1000);//time_to_sleep esta en milisegundo y usleep en microsegundos por eso mult. x 1000

    // Tomar tenedores (bloquear mutexes)
      if(philosopher->id % 2 == 0)
      {
        pthread_mutex_lock(philosopher->left_fork); // Tenedor de la izquierda
        printf("%ld Philosopher %d has taken left fork\n", get_time(), philosopher->id);

        pthread_mutex_lock(philosopher->right_fork); // Tenedor de la derecha
        printf("%ld Philosopher %d has taken right fork\n", get_time(), philosopher->id);
      }
      else 
      {
            pthread_mutex_lock(philosopher->right_fork);  // Lock right fork
            printf("%ld Philosopher %d has taken right fork\n", get_time(), philosopher->id);
            pthread_mutex_lock(philosopher->left_fork);   // Lock left fork
            printf("%ld Philosopher %d has taken left fork\n", get_time(), philosopher->id);
      }
    // Comer
      printf("%ld Philosopher %d is eating\n", get_time(), philosopher->id);
      usleep(philosopher->resources->time_to_eat * 1000); // Comer durante el tiempo de comer

    // Liberar tenedores (desbloquear mutexes)
      pthread_mutex_unlock(philosopher->left_fork); // Liberar tenedor de la izquierda
      pthread_mutex_unlock(philosopher->right_fork); // Liberar tenedor de la derecha

    // Dormir (reposo antes de empezar de nuevo)
      printf("%ld Philosopher %d is sleeping\n", get_time(), philosopher->id);
      usleep(philosopher->resources->time_to_sleep * 1000); // Dormir durante el tiempo de dormir
    }
    return NULL;
}

/*int monitor_philosopher(t_philosopher *philosopher, t_resources *resources)
{
    long current_time = get_time();
    if (current_time - philosopher->last_meal_time > philosopher->resources->time_to_die)
    {
        printf("%ld Philosopher %d died for time\n", current_time, philosopher->id);
        return (1); // Indica que el filósofo murió
    }
    if(philosopher->times_eaten > resources->eat_count)//REVISAR ESTA FUNCION HAY QUE ARREGLAR ESTO
    {
      printf("%ld Philosopher %d died for eat\n", current_time, philosopher->id);
        return (1); // Indica que el filósofo murió



    }
    return (0);
}*/
