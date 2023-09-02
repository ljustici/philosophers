/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljustici <ljustici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 17:21:57 by ljustici          #+#    #+#             */
/*   Updated: 2023/09/02 15:28:29 by ljustici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void report_action(char *msg, t_philo *philo)
{
    pthread_mutex_lock(philo->t->mtx_print);
    printf("[%lu] %i %s\n", get_current_time() - philo->t->start, philo->id, msg);
    pthread_mutex_unlock(philo->t->mtx_print);
}

int set_if_death(t_philo *philo, unsigned long activity)
{
    if (activity > philo->die_left || philo->die_left <= 0)
    {
        //pthread_mutex_lock(philo->t->mtx_cond);
        //philo->t->dead = philo->id; --> data race
        philo->is_dead = 1;
        report_action("is dead.", philo);
        //printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>><[%lu] Philosopher %i is dead. time left: %lu\n", get_current_time() - philo->t->start, philo->id, philo->die_left);
        //pthread_mutex_unlock(philo->t->mtx_cond);
        return (1);
    }
    return (0);
}

int do_try_fork(t_philo *philo, unsigned long time)
{
    int has_fork;

    pthread_mutex_lock(philo->t->mtx_fork);
    has_fork = 0;
    if (philo->fork_left && *(philo->fork_left) == 0 && philo->fork_right == 0)
    {
        *philo->fork_left = philo->id;
		//printf(">>>>>>>>>><philo %i FORK LEFT: %p\n", philo->id, philo->fork_left);
        report_action("has taken a fork.", philo);
		philo->fork_right = philo->id;
		//printf(">>>>>>>>>><philo %i FORK RIGHT: %p\n", philo->id, &philo->fork_right);
		report_action("has taken a fork.", philo);
		set_time_left(&philo->die_left, philo->die_time);
		report_action("is eating.", philo);
        pthread_mutex_unlock(philo->t->mtx_fork);
		ft_usleep(time);
        has_fork = 1;
        pthread_mutex_lock(philo->t->mtx_fork);
		philo->n_eaten++;
		release_forks(philo);
		set_time_left(&philo->die_left, philo->die_left - time);
    }
    pthread_mutex_unlock(philo->t->mtx_fork);
    return (has_fork);
}

void release_forks(t_philo *philo)
{
	if (philo->fork_left)
		*philo->fork_left = 0;
	philo->fork_right = 0;
}