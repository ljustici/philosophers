/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljustici <ljustici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 14:50:10 by ljustici          #+#    #+#             */
/*   Updated: 2023/08/30 20:04:16 by ljustici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void do_take(t_philo *philo)
{   
    set_fork_taken(&philo->fork_right,1);
    set_fork_taken(philo->fork_left,1);
	printf("[%lu] Philosopher %i has taken a fork.\n", get_current_time() - philo->start, philo->id);
	printf("[%lu] Philosopher %i has taken a fork.\n", get_current_time() - philo->start, philo->id);
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
            printf("%s[%lu] Philosopher %i is eating.%s time left: %lu\n", YELLOW, get_current_time() - philo->start, philo->id, NC, philo->die_left);
            ft_usleep(time);
            set_fork_taken(&philo->fork_right,0);
            set_fork_taken(philo->fork_left,0);
            pthread_mutex_unlock(mutex);
            if (is_dead(philo->die_left, philo->eat_time))
            {
                *(philo->total) = 0;
                philo->is_dead = 1;
                pthread_mutex_lock(mutex);
                printf("[%lu] Philosopher %i is dead.\n", get_current_time() - philo->start, philo->id);
                pthread_mutex_unlock(mutex);
            }
            else
                set_time_left(&philo->die_left, philo->die_left - time);
        }
    }
}

void do_sleep(t_philo *philo)
{
	unsigned long	time;
	pthread_mutex_t	*mtx_print;

    if (philo->is_dead)
        return ;
    time = get_routine_time(philo->die_time, philo->sleep_time);
    mtx_print = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(mtx_print, NULL);
	pthread_mutex_lock(mtx_print);
	printf("[%lu] Philosopher %i is sleeping. time left: %lu\n", get_current_time() - philo->start, philo->id, philo->die_left);
	pthread_mutex_unlock(mtx_print);
	ft_usleep(time);
    pthread_mutex_lock(mtx_print);
    if (is_dead(philo->die_left, philo->sleep_time))
    {
        *(philo->total) = 0;
        philo->is_dead = 1;
        printf("[%lu] Philosopher %i is dead. time left: %lu, time sleep: %lu\n", get_current_time() - philo->start, philo->id, philo->die_left, philo->sleep_time);
    }
    else
        set_time_left(&philo->die_left, philo->die_left - time);
    pthread_mutex_unlock(mtx_print);
}

void do_think(t_philo *philo)
{
    unsigned long   time;
    pthread_mutex_t *mtx_print;

    if (philo->is_dead)
        return ;
    mtx_print = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t));
    pthread_mutex_init(mtx_print, NULL);
    time = (philo->die_time - (philo->sleep_time + philo->eat_time)) * 0.01;
    pthread_mutex_lock(mtx_print);
    printf("[%lu] Philosopher %i is thinking. time left:%lu\n", get_current_time() - philo->start, philo->id, philo->die_left);
    pthread_mutex_unlock(mtx_print);
    ft_usleep(time);
    pthread_mutex_lock(mtx_print);
    if (is_dead(philo->die_left, time))
    {
        *(philo->total) = 0;
        philo->is_dead = 1;
        printf("[%lu] Philosopher %i is dead. time left: %lu\n", get_current_time() - philo->start, philo->id, philo->die_left);
    }
    else
        set_time_left(&philo->die_left, (philo->die_left - time));
    pthread_mutex_unlock(mtx_print);
}
