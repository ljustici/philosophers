/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljustici <ljustici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 14:50:10 by ljustici          #+#    #+#             */
/*   Updated: 2023/08/23 14:01:07 by ljustici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void do_take(t_philo *philo)
{
    struct timeval current_us;
    unsigned long current_ms;
    
    pthread_mutex_lock(&philo->fork_right);
    gettimeofday(&current_us, NULL);
    current_ms = get_ms(current_us.tv_usec);
	printf("[%lu] Philosopher %i has taken a fork.\n", current_ms, philo->id);
	pthread_mutex_lock(philo->fork_left);
	printf("[%lu] Philosopher %i has taken a fork.\n", current_ms, philo->id);
}

void do_eat(t_philo *philo)
{
    struct timeval current_us;
    unsigned long current_ms;
    
    gettimeofday(&current_us, NULL);
    current_ms = get_ms(current_us.tv_usec);
	printf("%s[%lu] Philosopher %i is eating.%s\n", YELLOW, current_ms, philo->id, NC);
    philo->die_left = philo->die_time;
	usleep(philo->eat_time);
    pthread_mutex_unlock(&philo->fork_right);
    pthread_mutex_unlock(philo->fork_left);
}

void do_sleep(t_philo *philo)
{
    unsigned long time;
    struct timeval current_us;
    unsigned long current_ms;

    gettimeofday(&current_us, NULL);
    current_ms = get_ms(current_us.tv_usec);
    if (philo->sleep_time > philo->die_time)
        time = philo->sleep_time - philo->die_time;
    else
        time = philo->sleep_time;
	printf("[%lu] Philosopher %i is sleeping.\n", current_ms, philo->id);
	usleep(time);
    if (philo->die_left > time)
        philo->die_left -= time;
    else
        philo->die_left = 0;
}

void do_think(t_philo *philo)
{
    unsigned long   time;
    struct timeval current_us;
    unsigned long current_ms;

    time = philo->die_time - philo->sleep_time;
    gettimeofday(&current_us, NULL);
    current_ms = get_ms(current_us.tv_usec);
    printf("[%lu] Philosopher %i is thinking.\n", current_ms, philo->id);
    usleep(time);
    if (philo->die_left > time)
        philo->die_left -= time;
    else
        philo->die_left = 0;
}