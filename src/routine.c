/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljustici <ljustici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 14:50:10 by ljustici          #+#    #+#             */
/*   Updated: 2023/09/01 19:33:46 by ljustici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void do_eat(t_philo *philo)
{
    unsigned long   time;
    int n_times;
    unsigned long start;
    
    n_times = 0;
    if (philo->is_dead)
        return ;
    time = get_routine_time(philo->die_time, philo->eat_time);
    start = get_current_time();
    while(n_times < 1 && philo->die_left > 0)
    {
        if (do_try_fork(philo, time))
            n_times = 1;
        else if (n_times == 0 && get_current_time() - start >= philo->die_left)
        {
            philo->die_left = 0;
            break;
        }
    }
    set_if_death(philo, time);
}

void do_sleep(t_philo *philo)
{
	unsigned long	time;

    if (philo->is_dead)
        return ;
    time = get_routine_time(philo->die_time, philo->sleep_time);
    report_action("is sleeping.", *philo);
	ft_usleep(time);
    set_time_left(&philo->die_left, (philo->die_left - time));
    set_if_death(philo, time);
}

void do_think(t_philo *philo)
{
    unsigned long   time;

    if (philo->is_dead)
        return ;
    time = (philo->die_time - (philo->sleep_time + philo->eat_time)) * 0.01;
    report_action("is thinking.", *philo);
    ft_usleep(time);
    set_time_left(&philo->die_left, (philo->die_left - time));
    set_if_death(philo, time);
}

void *routine(void *data)
{
	t_philo *philo = (t_philo *)data;
	int n;
	
	n = 0;
	while (check_cond(philo))
	{
		do_eat(philo);
		do_sleep(philo);
		do_think(philo);
	}
    pthread_mutex_lock(philo->t->mtx);
    if (philo->t->n_times != -1)
        philo->t->n_eaters++;
    pthread_mutex_unlock(philo->t->mtx);
	return (&philo->id);
}

int check_cond(t_philo *philo)
{
    int should_do;
    
    pthread_mutex_lock(philo->t->mtx);
    should_do = 0;
    if (philo->is_dead == 0 && (philo->n_eaten < philo->t->n_times || philo->t->n_times == -1))
        should_do = 1;
    pthread_mutex_unlock(philo->t->mtx);
    return (should_do);
}