/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljustici <ljustici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 11:20:36 by ljustici          #+#    #+#             */
/*   Updated: 2023/08/31 18:04:41 by ljustici         ###   ########.fr       */
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
    pthread_mutex_unlock(mtx_print);
    pthread_mutex_destroy(mtx_print);
}

void set_fork_taken(int *fork, int is_taken)
{
    if (is_taken)
        *fork = 1;
    else
        *fork = 0;
}
