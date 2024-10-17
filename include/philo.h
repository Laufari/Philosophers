#ifndef FT_PRINTF_H
# define FT_PRINTF_H

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

typedef struct	s_philosopher
{
    int		id;                     // Identificación del filósofo (número)
    long	last_meal_time;       // Tiempo de la última comida (timestamp)
    int		times_eaten;           // Número de veces que ha comido
    pthread_mutex_t *left_fork;   // Mutex para el tenedor izquierdo
    pthread_mutex_t *right_fork;  // Mutex para el tenedor derecho
    pthread_t thread;          // Hilo correspondiente al filósofo
    // Puedes añadir otros atributos como estado actual
    int		state;                 // 0: pensando, 1: comiendo, 2: durmiendo
    struct	s_resources *resources; // Puntero a recursos compartidos
}			t_philosopher;


typedef struct	s_resources
{
    pthread_mutex_t *forks;          // Array de mutex para los tenedores
    pthread_mutex_t print_mutex;     // Mutex para la impresión en consola (para evitar condiciones de carrera)
    int		number_of_philosophers;      // Total de filósofos
    long	time_to_die;                // Tiempo máximo antes de morir por inanición
    long	time_to_eat;                // Tiempo que tarda en comer
    long	time_to_sleep;              // Tiempo que tarda en dormir
    int		eat_count;                   // Número de veces que cada filósofo debe comer (opcional)
}			t_resources;

int	is_valid_num(char *str);
int parse_args(int argc, char **argv, t_resources *resources);


#endif