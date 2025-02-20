/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laufarin <laufarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 14:40:49 by laufarin          #+#    #+#             */
/*   Updated: 2025/02/20 15:56:30 by laufarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"


void    init(t_resources *resources, char **argv)
{
    resources->number_of_philosophers = ft_atoi(argv[1]);
	resources->time_to_die = ft_atoi(argv[2]);
	resources->time_to_eat = ft_atoi(argv[3]);
	resources->time_to_sleep = ft_atoi(argv[4]);
	

	if (argv[5])
		resources->eat_count = ft_atoi(argv[5]);  // Inicializa eat_count si hay un quinto argumento
	else
		resources->eat_count = -1;  // Valor por defecto si no se pasa un quinto argumento
}