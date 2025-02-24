/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_resources.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laufarin <laufarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 16:30:23 by laufarin          #+#    #+#             */
/*   Updated: 2025/02/24 20:07:49 by laufarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void    free_resources(pthread_t *thr, t_philosopher *phils, t_resources *resources)
{
    if(thr)
    {
        free(thr);
    }
    if(phils)
    {
        free(phils);
    }
    if(resources->forks)
    {  
        int i;

        i = 0;
        while(i < resources->number_of_philosophers)
        {
            pthread_mutex_destroy(&resources->forks[i]);
            i++;
        }
        free(resources->forks);
    }
}