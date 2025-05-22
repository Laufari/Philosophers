/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laufarin <laufarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 20:19:39 by laufarin          #+#    #+#             */
/*   Updated: 2025/05/19 13:07:48 by laufarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

//Esta función devuelve el tiempo en milisegundos
long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	precise_usleep(long miliseconds)
{
	long	init;
	long	elapsed;

	init = get_time();
	elapsed = init;
	while (elapsed < init + miliseconds)
	{
		usleep(100);
		elapsed = get_time();
	}
}
