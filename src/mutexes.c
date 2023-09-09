/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutexes.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljustici <ljustici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 18:07:37 by ljustici          #+#    #+#             */
/*   Updated: 2023/09/09 15:14:34 by ljustici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void set_forks(t_philo *philo)
{
	int i;
	int n;

	i = 0;
	n = philo->t->total;
	i = 0;
	while(i < n && n > 1)
	{
		if (i == n - 1)
			philo[i].fork_left = &philo[0].fork_right;
		else
			philo[i].fork_left = &philo[i + 1].fork_right;
		i++;
	}
}

void create_mutexes(t_table **table, t_philo *philo)
{
	int i ;
	
	(*table)->mtx_print = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t));
	(*table)->mtx_fork = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t));
	(*table)->mtx_nt = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t));
	(*table)->mtx_cond = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t));
	(*table)->mtx_check = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init((*table)->mtx_print, NULL);
	pthread_mutex_init((*table)->mtx_fork, NULL);
	pthread_mutex_init((*table)->mtx_nt, NULL);
	pthread_mutex_init((*table)->mtx_cond, NULL);
	pthread_mutex_init((*table)->mtx_check, NULL);
	i = 0;
	while (i < (*table)->total)
	{
		philo[i].mtx_fork_r = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t));
		pthread_mutex_init(philo[i].mtx_fork_r, NULL);
		i++;
	}
	i = 0;
	while (i < (*table)->total)
	{
		philo[i].mtx_fork_l = philo[i + 1].mtx_fork_r;
		if (i == (*table)->total - 1)
			philo[i].mtx_fork_l = philo[0].mtx_fork_r;
		i++;
	}
}

void destroy_mutexes(pthread_mutex_t *mutexes, int n)
{
	int i;

	i = 0;
	while(i < n)
	{
		if (pthread_mutex_destroy(mutexes) == -1)
			write(2, "Internal error: pthread_mutex_destroy failed.\n", 46);
		i++;
	}
}
