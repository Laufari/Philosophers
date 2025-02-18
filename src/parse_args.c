/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laufarin <laufarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 14:35:21 by laufarin          #+#    #+#             */
/*   Updated: 2025/02/18 16:18:56 by laufarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int parse_args(int argc, char **argv, t_resources *resources)
{
	(void)resources;//quitar
	if (argc < 5 || argc > 6)
	{
		printf("Error: Incorrect number of arguments\n");
		return (1);
	}
    // Verifica que haya entre 5 y 6 argumentos
	int	i;

	i = 1;
	while (i < argc)
	{
		if (!is_valid_num(argv[i]))
		{
			printf("Error: Argument %d is not a valid number.\n", i);
			return (1);
		}
		i++;
	}
	  // Verifica si el número de filósofos está entre 1 y 200
    if (ft_atoi(argv[1]) <= 0 || ft_atoi(argv[1]) > 200)
    {
        printf("Error: The number of philosophers must be between 1 and 200.\n");
        return (1);
    }
    return (0);  // Este return solo se ejecuta si todas las validaciones han pasado.
}

int	is_valid_num(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == 0)
			return (1);
		if (str[i] == '+')
			i++;
		if(str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}
