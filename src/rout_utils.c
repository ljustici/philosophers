/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rout_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljustici <ljustici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 18:07:37 by ljustici          #+#    #+#             */
/*   Updated: 2023/09/14 15:53:22 by ljustici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_mutexes(t_table **table, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < (*table)->total)
	{
		philo[i].mtx_fork_r = (pthread_mutex_t *)
			malloc(sizeof(pthread_mutex_t));
		pthread_mutex_init(philo[i].mtx_fork_r, NULL);
		i++;
	}
	i = 0;
	while (i < (*table)->total && (*table)->total > 1)
	{
		philo[i].mtx_fork_l = philo[i + 1].mtx_fork_r;
		if (i == (*table)->total - 1)
			philo[i].mtx_fork_l = philo[0].mtx_fork_r;
		i++;
	}
}

void	create_mutexes(t_table **table, t_philo *philo)
{
	(*table)->mtx_print = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	(*table)->mtx_nt = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	(*table)->mtx_cond = (pthread_mutex_t *) malloc(sizeof(pthread_mutex_t));
	(*table)->mtx_check = (pthread_mutex_t *) malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init((*table)->mtx_print, NULL);
	pthread_mutex_init((*table)->mtx_nt, NULL);
	pthread_mutex_init((*table)->mtx_cond, NULL);
	pthread_mutex_init((*table)->mtx_check, NULL);
	init_mutexes(table, philo);
}

void	destroy_mutexes(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->t->total)
	{
		if (pthread_mutex_destroy(philo[i].mtx_fork_r) == -1)
			write(2, "Internal error: pthread_mutex_destroy failed.\n", 46);
		i++;
	}
	if (pthread_mutex_destroy(philo->t->mtx_check) == -1)
		write(2, "Internal error: pthread_mutex_destroy failed.\n", 46);
	if (pthread_mutex_destroy(philo->t->mtx_cond) == -1)
		write(2, "Internal error: pthread_mutex_destroy failed.\n", 46);
	if (pthread_mutex_destroy(philo->t->mtx_print) == -1)
		write(2, "Internal error: pthread_mutex_destroy failed.\n", 46);
	if (pthread_mutex_destroy(philo->t->mtx_nt) == -1)
		write(2, "Internal error: pthread_mutex_destroy failed.\n", 46);
}

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

void	set_if_death(t_philo *philo)
{
	if (philo->die_left <= 0)
	{
		philo->is_dead = 1;
	}
}
