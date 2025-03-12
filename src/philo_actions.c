



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

void eat(t_philosopher *philosopher)
{
    // Comer
    print_status(philosopher, "is eating");
    pthread_mutex_lock(&philosopher->meal_mutex);
    philosopher->last_meal_time = get_time();
    printf("Philosopher %d updated last_meal_time to %ld\n", philosopher->id, philosopher->last_meal_time); //para borrar
    pthread_mutex_unlock(&philosopher->meal_mutex);
    philosopher->times_eaten++;
    usleep(philosopher->resources->time_to_eat * 1000); // Tiempo de comer
}

void put_down_forks(t_philosopher *philosopher)
{
    // Soltar los tenedores
    pthread_mutex_unlock(philosopher->left_fork);
    pthread_mutex_unlock(philosopher->right_fork);
}

void sleep_philosopher(t_philosopher *philosopher)
{
    // Dormir
    print_status(philosopher, "is sleeping");
    usleep(philosopher->resources->time_to_sleep * 1000); // Tiempo de dormir
}
