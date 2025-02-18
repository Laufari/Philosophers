/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laufarin <laufarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 20:19:39 by laufarin          #+#    #+#             */
/*   Updated: 2025/02/18 16:18:58 by laufarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"


// Esta función devuelve el tiempo en milisegundos
long get_time(void)
{
    struct timeval time;
    gettimeofday(&time, NULL); // Obtiene el tiempo actual
    return (time.tv_sec * 1000) + (time.tv_usec / 1000); // Convierte a milisegundos
}
