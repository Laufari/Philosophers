/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laufarin <laufarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 13:11:31 by laufarin          #+#    #+#             */
/*   Updated: 2025/05/22 11:25:33 by laufarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdlib.h>

typedef struct s_philosopher
{
	int					id;// Identificación del filósofo (número)
	long				last_meal_time;// Tiempo de última comida (timestamp)
	int					times_eaten;// Número de veces que ha comido
	pthread_mutex_t		meal_mutex;// Protege `last_meal_time`
	pthread_mutex_t		*left_fork;// Mutex para el tenedor izquierdo
	pthread_mutex_t		*right_fork;// Mutex para el tenedor derecho
	pthread_t			thread;// Hilo correspondiente al filósofo
	int					state;// 0: pensando, 1: comiendo, 2: durmiendo
	struct s_resources	*resources;// Puntero a recursos compartidos
}				t_philosopher;

typedef struct s_resources
{
	pthread_mutex_t	*forks;// Array de mutex para los tenedores
	pthread_mutex_t	print_mutex;// Mutex impresión consola(evitar cond.carrera)
	pthread_mutex_t	mutex;// Mutex sincronizar acceso a recursos compartidos
	pthread_mutex_t	start_mutex;
	pthread_mutex_t	full_mutex;
	t_philosopher	*philos;
	int				number_of_philosophers;// Total de filósofos
	long			time_to_die;// Tiempo máximo antes de morir por inanición
	long			time_to_eat;// Tiempo que tarda en comer
	long			time_to_sleep;// Tiempo que tarda en dormir
	int				eat_count;//N veces que cada filósofo debe comer (opcional)
	int				is_dead;
	int				can_eat;
	long			time_init;
	int				num_philos_full;
}				t_resources;

int		is_valid_num(char *str);
int		parse_args(int argc, char **argv);
void	init_resources(t_resources *resources, char **argv);
void	free_resources(pthread_t *thr, t_resources *resources);
int		mem_hilos(pthread_t **threads, t_resources *resources);
int		create_philos(pthread_t **threads, t_resources *resources);
int		init_forks(t_resources *resources);
void	print_status(t_philosopher *philosopher, char *message);

int		init_printmutex(t_resources *resources);

//UTILS

int		ft_atoi(char *str);
int		is_space(char c);

//PHILOSOPHERS

void	*philosopher_life(void *arg);
int		monitor_philosophers(t_resources *resources);

//TIME_UTILS

long	get_time(void);
void	precise_usleep(long miliseconds);

void	take_forks(t_philosopher *philosopher);
int		eat(t_philosopher *philosopher);
void	put_down_forks(t_philosopher *philosopher);
void	sleep_philosopher(t_philosopher *philosopher);
void	think(t_philosopher *philosopher);
void	ft_destroy(t_resources *resources);

#endif
