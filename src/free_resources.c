/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_resources.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laufarin <laufarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 16:30:23 by laufarin          #+#    #+#             */
/*   Updated: 2025/02/19 16:52:40 by laufarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void    free_resources(pthread_t *thr, t_philosopher *phils)
{
    if(thr)
    {
        free(thr);
    }
    if(phils)
    {
        free(phils);
    }
}