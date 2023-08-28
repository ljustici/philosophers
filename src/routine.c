/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljustici <ljustici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 14:50:10 by ljustici          #+#    #+#             */
/*   Updated: 2023/08/28 16:47:40 by ljustici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void do_take(t_philo *philo)
{   
    philo->fork_right = 1;
	printf("[%lu] Philosopher %i has taken a fork.\n", get_current_time(), philo->id);
    *(philo->fork_left) = 1;
	printf("[%lu] Philosopher %i has taken a fork.\n", get_current_time(), philo->id);
}

void do_eat(t_philo *philo)
{
    pthread_mutex_t mutex;
    
    if (philo->die_left <= 0 || *(philo->total) == 0)
        return ;
    pthread_mutex_init(&mutex, NULL);
    if (pthread_mutex_lock(&mutex) != 0)
        pthread_mutex_unlock(&mutex);
    else
    {
        do_take(philo);
        printf("%s[%lu] Philosopher %i is eating.%s\n", YELLOW, get_current_time(), philo->id, NC);
        philo->die_left = philo->die_time;
        usleep(philo->eat_time);
        pthread_mutex_unlock(&mutex);
		if (philo->eat_time > philo->die_time)
			philo->is_dead = 1;
    }
}

void do_sleep(t_philo *philo)
{
	unsigned long	time;
	pthread_mutex_t	mtx_print;

	pthread_mutex_init(&mtx_print, NULL);
	if (philo->die_left <= 0 || *(philo->total) == 0)
		return ;
	if (philo->sleep_time > philo->die_time)
		time = philo->sleep_time - philo->die_time;
	else
		time = philo->sleep_time;
	pthread_mutex_lock(&mtx_print);
	printf("[%lu] Philosopher %i is sleeping.\n", get_current_time(), philo->id);
	pthread_mutex_unlock(&mtx_print);
	usleep(time);
	if (philo->die_left > time)
		philo->die_left -= time;
	else
	{
		philo->die_left = 0;
		philo->total = 0;
	}
}

void do_think(t_philo *philo)
{
    unsigned long   time;
    pthread_mutex_t mtx_print;

    pthread_mutex_init(&mtx_print, NULL);
    if (philo->die_left <= 0 || *(philo->total) == 0)
        return ;
    time = philo->die_time - philo->sleep_time;
    pthread_mutex_lock(&mtx_print);
    printf("[%lu] Philosopher %i is thinking.\n", get_current_time(), philo->id);
    pthread_mutex_unlock(&mtx_print);
    usleep(time);
    if (philo->die_left > time)
        philo->die_left -= time;
    else
    {
        philo->die_left = 0;
        philo->total = 0;
    }
}