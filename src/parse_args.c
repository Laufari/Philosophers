/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laufarin <laufarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 14:35:21 by laufarin          #+#    #+#             */
/*   Updated: 2024/10/17 15:50:25 by laufarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_valid_num(char *str)
{
	int	i;

	i = 0;
	while(str[i])
	{
		if(str[i] == 0)
			return(0);
		if(str[i] < '0' || str[i] > '9')
			return(0);
		i++;
	}
	return(1);
}


int parse_args(int argc, char **argv, t_resources *resources)
{
	(void)resources;//quitar
	if(argc < 5 || argc > 6)
		printf("Error: Incorrect number of arguments\n");
    // Verifica que haya entre 5 y 6 argumentos
	int	i;

	i = 1;
	while(i < argc)
	{
		if(!is_valid_num(argv[i]))
		{
			printf("Error: Argument %d is not a valid number.\n", i);
			return(0);
		}
		i++;
	}

	// resources-> number_of_philosophers = atoi(argv[1]);
	// resources-> time_to_die = atoi(argv[2]);
	// resources->time_to_eat = atoi(argv[3]);//no olvidar quitar atoi
	// resources->time_to_sleep = atoi(argv[4]);
	return(1);
}
