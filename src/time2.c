/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljustici <ljustici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 19:54:38 by ljustici          #+#    #+#             */
/*   Updated: 2023/08/31 17:16:53 by ljustici         ###   ########.fr       */
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

unsigned long get_ms(suseconds_t usecs)
{
	return (usecs/1000);
}

unsigned long get_us(unsigned long ms)
{
	return (ms*1000);
}

unsigned long	get_current_time()
{
	struct timeval current_us;
	
	gettimeofday(&current_us, NULL);
	return(current_us.tv_sec * 1000 + current_us.tv_usec / 1000);
}
