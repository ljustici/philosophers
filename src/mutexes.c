/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutexes.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljustici <ljustici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 18:07:37 by ljustici          #+#    #+#             */
/*   Updated: 2023/08/23 11:52:20 by ljustici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void create_mutexes(t_philo *philo)
{
	int i;
	int n;

	i = 0;
	n = philo->total;
	while(i < philo->total)
	{
		if (pthread_mutex_init(&philo[i].fork_right, NULL) == -1)
			printf("Error: pthread_mutex_init failed.\n");
		i++;
	}
	i = 0;
	while(i < philo->total)
	{
		if (i == 0)
			philo[i].fork_left = &philo[n-1].fork_right;
		else
			philo[i].fork_left = &philo[i + 1].fork_right;
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
			printf("Error: pthread_mutex_destroy failed.\n");
		i++;
	}
}