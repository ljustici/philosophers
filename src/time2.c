/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljustici <ljustici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 19:54:38 by ljustici          #+#    #+#             */
/*   Updated: 2023/08/30 20:16:35 by ljustici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void ft_usleep(unsigned long time)
{
    unsigned long start;

    start = get_current_time();
    //printf("%lu\n",time);
    //cambiar start al programa en lugar de a cada philo 
    while (get_current_time() - start < time)
    {
        usleep(1000);
    }   
}
