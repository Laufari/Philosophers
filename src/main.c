/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laufarin <laufarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 15:54:24 by laufarin          #+#    #+#             */
/*   Updated: 2025/02/18 16:18:54 by laufarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int main(int argc, char **argv)
{
	t_resources resources;

	// Primero, valida los argumentos
	if (parse_args(argc, argv, &resources))
	{
		return (1);  // Si hay un error en los argumentos, sale del programa
	}

	// Ahora, inicializa los valores en la estructura `resources`
	resources.number_of_philosophers = ft_atoi(argv[1]);
	resources.time_to_die = ft_atoi(argv[2]);
	resources.time_to_eat = ft_atoi(argv[3]);
	resources.time_to_sleep = ft_atoi(argv[4]);
	

	if (argc == 6)
		resources.eat_count = ft_atoi(argv[5]);  // Inicializa eat_count si hay un quinto argumento
	else
		resources.eat_count = -1;  // Valor por defecto si no se pasa un quinto argumento

	// Aquí iría el resto de la lógica del programa, como crear hilos, inicializar mutexes, etc.
	
	//PARA BORRAR:
	printf("Num of philos: %d\n", resources.number_of_philosophers);
	printf("time to die: %ld\n", resources.time_to_die);
	printf("time to eat: %ld\n", resources.time_to_eat);
	printf("time to sleep: %ld\n", resources.time_to_sleep);
	printf("eat count: %d\n", resources.eat_count);

	pthread_t *threads;
	t_philosopher *philos;
	int	i;

	i = 0;
	threads = malloc(sizeof(pthread_t) * resources.number_of_philosophers);
	philos = malloc(sizeof(t_philosopher) * resources.number_of_philosophers);

	if (!threads || !philos)
    {
        printf("Error allocating memory for philosophers or threads.\n");
        return (1);
    }
	while(i < resources.number_of_philosophers)//creamos filosofos y asignamos propiedades
	{

		philos[i].id = i + 1;
		philos[i].resources = &resources;

		//creamos hilos para e filosofo
		if (pthread_create(&threads[i], NULL, philosopher_life, (void *)&philos[i]) != 0)
		{
			printf("Error creating thread.\n");
			return (1);
		}
		i++;
	}
	// Unir los hilos para esperar que terminen
    i = 0;
    while (i < resources.number_of_philosophers)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
	// Liberar memoria
    free(threads);
    free(philos);
	return (0);
}

