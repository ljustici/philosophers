/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljustici <ljustici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 14:50:10 by ljustici          #+#    #+#             */
/*   Updated: 2023/09/15 18:09:55 by ljustici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	philo->start = 1;
	while (is_there_start(philo) == 0)
		usleep(100);
	if (philo->id % 2 != 0)
		usleep(40);
	philo->die_left = get_current_time();
	while (check_cond(philo))
	{
		if (philo->id % 2 == 0)
		{
			do_eat(philo);
			do_sleep(philo);
			do_think(philo);
		}
		else
		{
			do_sleep(philo);
			do_think(philo);
			do_eat(philo);
		}
	}
	return (&philo->id);
}

void	do_eat(t_philo *philo)
{
	int				n_times;
	unsigned long	start;

	n_times = 0;
	if (!check_cond(philo))
		return ;
	while (n_times < 1 && time_last_eat(philo) == 0)
	{
		start = get_current_time();
		if (do_try_fork(philo) == 1)
			n_times = 1;
	}
}

void	do_sleep(t_philo *philo)
{
	int				should_die;

	if (!check_cond(philo))
		return ;
	should_die = should_philo_die(philo, philo->sleep_time);
	report_action("is sleeping", *philo);
	if (should_die)
	{
		ft_usleep(philo->die_time - get_t_last_eat(philo));
		philo->is_dead = 1;
	}
	else
		ft_usleep(philo->sleep_time);
}

void	do_think(t_philo *philo)
{
	unsigned long	time;

	if (!check_cond(philo))
		return ;
	if (philo->die_time > (philo->sleep_time + philo->eat_time))
		time = (philo->die_time - (philo->sleep_time + philo->eat_time)) * 0.01;
	else
		time = 0;
	report_action("is thinking", *philo);
	ft_usleep(time);
}

int	check_cond(t_philo *philo)
{
	int	should_do;
	int	all_ate;

	pthread_mutex_lock(philo->t->mtx_cond);
	should_do = 0;
	all_ate = did_all_eat(philo);
	if (philo->is_dead == 0 && all_ate == 0 && is_there_dead(philo) == 0)
		should_do = 1;
	else
		set_stop(philo, all_ate);
	pthread_mutex_unlock(philo->t->mtx_cond);
	return (should_do);
}
