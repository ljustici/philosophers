/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljustici <ljustici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 11:20:36 by ljustici          #+#    #+#             */
/*   Updated: 2023/09/10 16:15:51 by ljustici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

unsigned long get_routine_time(unsigned long die, unsigned long activity)
{
    unsigned long time;

    if (activity > die)
        time = activity - die;
    else
        time = activity;
    return (time);
}

void set_time_left(unsigned long *die, unsigned long new)
{
    pthread_mutex_t *mtx_print;

    mtx_print = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t));
    pthread_mutex_init(mtx_print, NULL);
    pthread_mutex_lock(mtx_print);
    *die = new;
    if (*die < 0)
        *die = 0;
    pthread_mutex_unlock(mtx_print);
    pthread_mutex_destroy(mtx_print);
}

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

unsigned long	get_current_time()
{
	struct timeval current_us;
	
	gettimeofday(&current_us, NULL);
	return(current_us.tv_sec * 1000 + current_us.tv_usec / 1000);
}
