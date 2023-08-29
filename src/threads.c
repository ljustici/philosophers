/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljustici <ljustici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 18:07:02 by ljustici          #+#    #+#             */
/*   Updated: 2023/08/29 17:15:15 by ljustici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void create_threads(t_philo *philo)
{
	int i;

	i = 0;
	set_forks(philo);
	while(i < *(philo->total))
	{
		if (pthread_create(&philo[i].philo, NULL, routine, &philo[i]) == -1)
			printf("Error: pthread_create failed.\n");
		else
		{
			philo[i].id = i + 1;
			
		}
		i++;
	}
}

void join_thread(t_philo *philo)
{
	void *rvalue = NULL;
	pthread_join(philo->philo, &rvalue);
	printf("Philosopher [%i] has died.\n", *(int*)rvalue);
}

void join_threads(t_philo *philo)
{
	int i;

	i = 0;
	while (i < *(philo->total))
	{
		pthread_join(philo[i].philo, NULL);
		printf("Philosopher [%i] has died.\n", philo[i].id);
		i++;
	}
}
