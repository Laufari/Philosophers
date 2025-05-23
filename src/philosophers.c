/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laufarin <laufarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 17:42:08 by laufarin          #+#    #+#             */
/*   Updated: 2025/05/23 16:00:19 by laufarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*philosopher_life(void *arg)
{
	t_philosopher	*philosopher;

	philosopher = (t_philosopher *)arg;
	if (philosopher->resources->number_of_philosophers == 1)
		return (handle_single_philosopher(arg));
	if (philosopher->id % 2 == 0)
		precise_usleep(2);
	if (philosopher->id % 2 == 0)
		precise_usleep(2);
	while (1)
	{
		if (should_stop_execution(philosopher))
			break ;
		take_forks(philosopher);
		eat(philosopher);
		put_down_forks(philosopher);
		sleep_philosopher(philosopher);
		think(philosopher);
	}
	return (NULL);
}

static int	check_philo_death(t_resources *res, int i, long current_time)
{
	long	last_meal;

	last_meal = res->philos[i].last_meal_time;
	if ((res->philos[i].times_eaten < res->eat_count)
		&& current_time - last_meal > res->time_to_die)
	{
		pthread_mutex_lock(&res->print_mutex);
		res->is_dead = 1;
		printf("%ld %d died\n", current_time - res->time_init,
			res->philos[i].id);
		pthread_mutex_unlock(&res->print_mutex);
		pthread_mutex_unlock(&res->philos[i].meal_mutex);
		return (1);
	}
	return (0);
}

static int	check_all_full(t_resources *res)
{
	pthread_mutex_lock(&res->full_mutex);
	if (res->num_philos_full >= res->number_of_philosophers)
	{
		pthread_mutex_unlock(&res->full_mutex);
		return (1);
	}
	pthread_mutex_unlock(&res->full_mutex);
	return (0);
}

int	monitor_philosophers(t_resources *resources)
{
	long	current_time;
	int		i;

	while (1)
	{
		i = -1;
		while (++i < resources->number_of_philosophers)
		{
			pthread_mutex_lock(&resources->philos[i].meal_mutex);
			current_time = get_time();
			if (check_philo_death(resources, i, current_time))
				return (1);
			pthread_mutex_unlock(&resources->philos[i].meal_mutex);
			if (check_all_full(resources))
				return (0);
		}
		precise_usleep(1);
	}
	return (0);
}
