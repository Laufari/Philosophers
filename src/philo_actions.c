/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laufarin <laufarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 13:43:40 by laufarin          #+#    #+#             */
/*   Updated: 2025/05/22 15:52:19 by laufarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_forks(t_philosopher *philosopher)
{
	if (philosopher->id % 2 == 0)
	{
		pthread_mutex_lock(philosopher->left_fork);
		print_status(philosopher, "has taken a fork");
		pthread_mutex_lock(philosopher->right_fork);
		print_status(philosopher, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philosopher->right_fork);
		print_status(philosopher, "has taken a fork");
		pthread_mutex_lock(philosopher->left_fork);
		print_status(philosopher, "has taken a fork");
	}
}

void	put_down_forks(t_philosopher *philosopher)
{
	pthread_mutex_unlock(philosopher->left_fork);
	pthread_mutex_unlock(philosopher->right_fork);
}

int	eat(t_philosopher *philosopher)
{
	pthread_mutex_lock(&philosopher->meal_mutex);
	philosopher->last_meal_time = get_time();
	pthread_mutex_unlock(&philosopher->meal_mutex);
	print_status(philosopher, "is eating");
	precise_usleep(philosopher->resources->time_to_eat);
	pthread_mutex_lock(&philosopher->meal_mutex);
	philosopher->times_eaten++;
	pthread_mutex_unlock(&philosopher->meal_mutex);
	return (0);
}

void	sleep_philosopher(t_philosopher *philosopher)
{
	print_status(philosopher, "is sleeping");
	precise_usleep(philosopher->resources->time_to_sleep);
}

void	think(t_philosopher *philosopher)
{
	print_status(philosopher, "is thinking");
}
