/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljustici <ljustici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 18:07:02 by ljustici          #+#    #+#             */
/*   Updated: 2023/09/10 17:15:40 by ljustici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void create_threads(t_philo *philo)
{
	int i;

	i = 0;
	set_forks(philo);
	pthread_mutex_lock(philo->t->mtx_print);
	philo->t->start = get_current_time();
	pthread_mutex_unlock(philo->t->mtx_print);
	while(i < philo->t->total)
	{
		if (pthread_create(&philo[i].philo, NULL, routine, &philo[i]) == -1)
			printf("Error: pthread_create failed.\n");
		i++;
	}
}

void join_thread(t_philo *philo)
{
	void *rvalue = NULL;
	pthread_join(philo->philo, &rvalue);
}

void join_threads(t_philo *philo)
{
	int i;

	i = 0;
	while (i < philo->t->total)
	{
		pthread_join(philo[i].philo, NULL);
		i++;
	}
}
