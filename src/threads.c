/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljustici <ljustici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 18:07:02 by ljustici          #+#    #+#             */
/*   Updated: 2023/08/22 14:52:08 by ljustici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void create_threads(t_philo *philo, int n)
{
	int i;

	i = 0;
	create_mutexes(philo, n);
	while(i < n)
	{
		if (pthread_create(&philo[i].philo, NULL, routine, &philo[i]) == -1)
			printf("Error: pthread_create failed.\n");
		else
		{
			philo[i].id = i + 1;
			//printf("Created thread [%ld] as Philosopher %i\n", (long)philo[i].philo, philo[i].id);
		}
		i++;
	}
}

void join_threads(t_philo *philo, int n)
{
	int i;

	i = 0;
	while (i < n)
	{
		pthread_join(philo[i].philo, NULL);
		printf("Main: Joining thread [%ld]\n", (long)philo[i].philo);
		i++;
	}
}