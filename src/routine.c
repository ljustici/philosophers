/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljustici <ljustici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 14:50:10 by ljustici          #+#    #+#             */
/*   Updated: 2023/08/31 18:05:14 by ljustici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void do_take(t_philo *philo)
{   
    set_fork_taken(&philo->fork_right,1);
    set_fork_taken(philo->fork_left,1);
	printf("[%lu] Philosopher %i has taken a fork.\n", get_current_time() - philo->t->start, philo->id);
	printf("[%lu] Philosopher %i has taken a fork.\n", get_current_time() - philo->t->start, philo->id);
}

void do_eat(t_philo *philo)
{
    pthread_mutex_t *mutex;
    unsigned long   time;
    
    if (philo->is_dead)
        return ;
    time = get_routine_time(philo->die_time, philo->eat_time);
    mutex = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t));
    pthread_mutex_init(mutex, NULL);
    if (pthread_mutex_lock(mutex) != 0)
        pthread_mutex_unlock(mutex);
    else
    {
        if (!philo->fork_left || *(philo->fork_left) == 1 || philo->fork_right == 1)
            pthread_mutex_unlock(mutex);
        else
        {
            set_time_left(&philo->die_left, philo->die_time);
            do_take(philo);
            printf("%s[%lu] Philosopher %i is eating.%s time left: %lu\n", YELLOW, get_current_time() - philo->t->start, philo->id, NC, philo->die_left);
            ft_usleep(time);
            set_fork_taken(&philo->fork_right,0);
            set_fork_taken(philo->fork_left,0);
            pthread_mutex_unlock(mutex);
            if (set_if_death(philo, time) == 0)
                set_time_left(&philo->die_left, (philo->die_left - time));
        }
    }
}

void do_sleep(t_philo *philo)
{
	unsigned long	time;

    if (philo->is_dead)
        return ;
    time = get_routine_time(philo->die_time, philo->sleep_time);
    report_action("is sleeping.", *philo);
	ft_usleep(time);
    if (set_if_death(philo, time) == 0)
        set_time_left(&philo->die_left, (philo->die_left - time));
}

void do_think(t_philo *philo)
{
    unsigned long   time;

    if (philo->is_dead)
        return ;
    time = (philo->die_time - (philo->sleep_time + philo->eat_time)) * 0.01;
    report_action("is thinking.", *philo);
    ft_usleep(time);
    if (set_if_death(philo, time) == 0)
        set_time_left(&philo->die_left, (philo->die_left - time));
}
