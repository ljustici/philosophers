/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutexes.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljustici <ljustici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 18:07:37 by ljustici          #+#    #+#             */
/*   Updated: 2023/08/28 16:52:09 by ljustici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void set_forks(t_philo *philo)
{
	int i;
	int n;

	i = 0;
	n = *(philo->total);
	i = 0;
	while(i < n)
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
			write(2, "Internal error: pthread_mutex_destroy failed.\n", 46);
		i++;
	}
}