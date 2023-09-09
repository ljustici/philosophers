/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljustici <ljustici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 17:21:57 by ljustici          #+#    #+#             */
/*   Updated: 2023/09/09 15:44:43 by ljustici         ###   ########.fr       */
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
    (void)activity;
    if (!check_cond(philo))
        return (0);
    if (philo->die_left <= 0)
    {
        philo->is_dead = 1;
        report_action("died.", philo);
        return (1);
    }
    return (0);
}

int do_try_fork(t_philo *philo, unsigned long time)
{
    int has_fork;

    if (!check_cond(philo))
        return (0);
    has_fork = 0;
    if (grab_forks(philo) == 2)
    {
        report_action("has taken a fork.", philo);
        report_action("has taken a fork.", philo);
        set_time_left(&philo->die_left, philo->die_time);
        report_action("is eating.", philo);
        has_fork = 1;
        ft_usleep(time);
        philo->n_eaten++;
        release_forks(philo);
        set_time_left(&philo->die_left, philo->die_left - time);
        set_eater(philo);
    }
    return (has_fork);
}

/*int do_try_fork(t_philo *philo, unsigned long time)
{
    int has_fork;

    if (!check_cond(philo))
        return (0);
    pthread_mutex_lock(philo->t->mtx_fork);
    has_fork = 0;
    if (philo->fork_left && *(philo->fork_left) == 0 && philo->fork_right == 0)
    {
        *philo->fork_left = philo->id;
        report_action("has taken a fork.", philo);
		philo->fork_right = philo->id;
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
        set_eater(philo);
    }
    pthread_mutex_unlock(philo->t->mtx_fork);
    return (has_fork);
}*/

void set_stop(t_philo *philo)
{
    pthread_mutex_lock(philo->t->mtx_check);
    philo->t->dead = philo->id;
    pthread_mutex_unlock(philo->t->mtx_check);
}

int is_there_dead(t_philo *philo)
{
    int is_dead;
    pthread_mutex_lock(philo->t->mtx_check);
    if (philo->t->dead != 0)
        is_dead = 1;
    else
        is_dead = 0;
    pthread_mutex_unlock(philo->t->mtx_check);
    return (is_dead);
}

void set_eater(t_philo *philo)
{
    pthread_mutex_lock(philo->t->mtx_nt);
    if (philo->n_eaten == philo->t->n_times)
        philo->t->n_eaters++;
    pthread_mutex_unlock(philo->t->mtx_nt);
}

int did_all_eat(t_philo *philo)
{
    int have_eaten;

    pthread_mutex_lock(philo->t->mtx_nt);
    if (philo->t->n_eaters == philo->t->total)
        have_eaten = 1;
    else
        have_eaten = 0;
    pthread_mutex_unlock(philo->t->mtx_nt);
    return (have_eaten);
}

int grab_forks(t_philo *philo)
{
    int has_forks;

    has_forks = 0;
    pthread_mutex_lock(philo->mtx_fork_l);
    if (*philo->fork_left == 0)
    {
        *philo->fork_left = philo->id;
        has_forks++;
    }
    pthread_mutex_lock(philo->mtx_fork_r);
    if (philo->fork_right == 0)
    {
        philo->fork_right = philo->id;
        has_forks++;
    }
    pthread_mutex_unlock(philo->mtx_fork_r);
    pthread_mutex_unlock(philo->mtx_fork_l);
    return (has_forks);
}

void release_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->mtx_fork_l);
    *philo->fork_left = 0;
    pthread_mutex_lock(philo->mtx_fork_r);
    philo->fork_right = 0;
    pthread_mutex_unlock(philo->mtx_fork_r);
    pthread_mutex_unlock(philo->mtx_fork_l);
}
