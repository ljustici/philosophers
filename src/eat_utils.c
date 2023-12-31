/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljustici <ljustici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 17:21:57 by ljustici          #+#    #+#             */
/*   Updated: 2023/09/15 18:10:01 by ljustici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	do_try_fork(t_philo *philo)
{
	int				has_fork;

	if (!check_cond(philo))
		return (0);
	has_fork = grab_forks(philo);
	if (has_fork == 2)
	{
		philo->die_left = get_current_time();
		eating(philo);
		has_fork = 1;
		release_forks(philo);
		philo->n_eaten++;
		set_eater(philo);
	}
	else if (has_fork)
	{
		release_forks(philo);
		has_fork = 0;
	}
	return (has_fork);
}

void	set_eater(t_philo *philo)
{
	pthread_mutex_lock(philo->t->mtx_nt);
	if (philo->n_eaten == philo->t->n_times)
		philo->t->n_eaters++;
	pthread_mutex_unlock(philo->t->mtx_nt);
}

int	did_all_eat(t_philo *philo)
{
	int	have_eaten;

	pthread_mutex_lock(philo->t->mtx_nt);
	if (philo->t->n_eaters == philo->t->total)
		have_eaten = 1;
	else
		have_eaten = 0;
	pthread_mutex_unlock(philo->t->mtx_nt);
	return (have_eaten);
}

int	grab_forks(t_philo *philo)
{
	int	has_forks;

	has_forks = 0;
	if (!philo->mtx_fork_l)
		return (has_forks);
	pthread_mutex_lock(philo->mtx_fork_l);
	if (*philo->fork_left == 0)
	{
		*philo->fork_left = philo->id;
		has_forks++;
		pthread_mutex_lock(philo->mtx_fork_r);
		if (philo->fork_right == 0)
		{
			philo->fork_right = philo->id;
			report_action("has taken a fork", *philo);
			report_action("has taken a fork", *philo);
			has_forks++;
		}
		pthread_mutex_unlock(philo->mtx_fork_r);
	}
	pthread_mutex_unlock(philo->mtx_fork_l);
	return (has_forks);
}

void	release_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->mtx_fork_l);
	if (*philo->fork_left == philo->id)
		*philo->fork_left = 0;
	pthread_mutex_unlock(philo->mtx_fork_l);
	pthread_mutex_lock(philo->mtx_fork_r);
	if (philo->fork_right == philo->id)
		philo->fork_right = 0;
	pthread_mutex_unlock(philo->mtx_fork_r);
}
