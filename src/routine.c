/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljustici <ljustici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 14:50:10 by ljustici          #+#    #+#             */
/*   Updated: 2023/08/22 16:44:26 by ljustici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void do_take(t_philo *philo)
{
    pthread_mutex_lock(&philo->fork_right);
	printf("Philosopher %i has taken a fork.\n", philo->id);
	pthread_mutex_lock(philo->fork_left);
	printf("Philosopher %i has taken a fork.\n", philo->id);
}

void do_eat(t_philo *philo)
{
	printf("Philosopher %i is eating.\n", philo->id);
	usleep(philo->eat_time);
    pthread_mutex_unlock(&philo->fork_right);
    pthread_mutex_unlock(philo->fork_left);
}

void do_sleep(t_philo *philo)
{
    unsigned long time;

    if (philo->sleep_time < philo->die_time)
        time = philo->die_time - philo->sleep_time;
    else
        time = philo->sleep_time - philo->die_time;
	printf("Philosopher %i is sleeping.\n", philo->id);
	usleep(time);
}

void do_think(t_philo philo)
{
	printf("Philosopher %i is thinking.\n", philo.id);
}