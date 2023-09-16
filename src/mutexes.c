/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutexes.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljustici <ljustici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 15:55:14 by ljustici          #+#    #+#             */
/*   Updated: 2023/09/16 17:18:52 by ljustici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	init_table_mutexes(t_table **table, t_philo *philo)
{
	int	i;

	(*table)->mtx_check = (pthread_mutex_t *) malloc(sizeof(pthread_mutex_t));
	if (!(*table)->mtx_check)
	{
		free((*table)->mtx_print);
		free((*table)->mtx_nt);
		free((*table)->mtx_cond);
		return (-1);
	}
	pthread_mutex_init((*table)->mtx_print, NULL);
	pthread_mutex_init((*table)->mtx_nt, NULL);
	pthread_mutex_init((*table)->mtx_cond, NULL);
	pthread_mutex_init((*table)->mtx_check, NULL);
	if (create_philo_mutexes(table, philo) != 0)
		return (-1);
	i = 0;
	while (i < (*table)->total && (*table)->total > 1)
	{
		philo[i].mtx_fork_l = philo[i + 1].mtx_fork_r;
		if (i == (*table)->total - 1)
			philo[i].mtx_fork_l = philo[0].mtx_fork_r;
		i++;
	}
	return (0);
}

int	create_philo_mutexes(t_table **table, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < (*table)->total)
	{
		philo[i].mtx_fork_r = (pthread_mutex_t *)
			malloc(sizeof(pthread_mutex_t));
		if (!philo[i].mtx_fork_r)
		{
			while (i-- > 0)
				free(philo[i].mtx_fork_r);
			return (-1);
		}
		pthread_mutex_init(philo[i].mtx_fork_r, NULL);
		i++;
	}
	return (0);
}

int	create_mutexes(t_table **table, t_philo *philo)
{
	(*table)->mtx_print = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	if (!(*table)->mtx_print)
		return (-1);
	(*table)->mtx_nt = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	if (!(*table)->mtx_nt)
	{
		free((*table)->mtx_print);
		return (-1);
	}
	(*table)->mtx_cond = (pthread_mutex_t *) malloc(sizeof(pthread_mutex_t));
	if (!(*table)->mtx_cond)
	{
		free((*table)->mtx_print);
		free((*table)->mtx_nt);
		return (-1);
	}
	if (init_table_mutexes(table, philo) != 0)
		return (-1);
	return (0);
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

void	set_forks(t_philo *philo)
{
	int	i;
	int	n;

	i = 0;
	n = philo->t->total;
	i = 0;
	while (i < n && n > 1)
	{
		if (i == n - 1)
			philo[i].fork_left = &philo[0].fork_right;
		else
			philo[i].fork_left = &philo[i + 1].fork_right;
		i++;
	}
}
