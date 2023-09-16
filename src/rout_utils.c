/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rout_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljustici <ljustici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 18:07:37 by ljustici          #+#    #+#             */
/*   Updated: 2023/09/16 16:28:08 by ljustici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	is_there_dead(t_philo *philo)
{
	int	is_dead;

	pthread_mutex_lock(philo->t->mtx_check);
	if (philo->t->dead != 0)
		is_dead = philo->t->dead;
	else
		is_dead = 0;
	pthread_mutex_unlock(philo->t->mtx_check);
	return (is_dead);
}

void	eating(t_philo *philo)
{
	int				should_die;

	should_die = should_philo_die(philo, philo->eat_time);
	report_action("is eating", *philo);
	if (should_die)
	{
		ft_usleep(philo->die_time - get_t_last_eat(philo));
		philo->is_dead = 1;
	}
	else
		ft_usleep(philo->eat_time);
}

void	free_philos(t_philo *philo)
{
	int	i;

	i = 0;
	free(philo->t->mtx_print);
	free(philo->t->mtx_nt);
	free(philo->t->mtx_cond);
	free(philo->t->mtx_check);
	while (i < philo->t->total)
	{
		free(philo[i].mtx_fork_r);
		i++;
	}
	free(philo);
}

void	set_stop(t_philo *philo, int all_ate)
{
	if (all_ate)
		return ;
	else
	{
		pthread_mutex_lock(philo->t->mtx_check);
		philo->t->dead = philo->id;
		pthread_mutex_unlock(philo->t->mtx_check);
	}
}

void	report_action(char *msg, t_philo philo)
{
	pthread_mutex_lock(philo.t->mtx_print);
	printf("%lu %i %s\n", get_current_time() - philo.t->start, philo.id, msg);
	pthread_mutex_unlock(philo.t->mtx_print);
}
