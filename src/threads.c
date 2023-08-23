/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljustici <ljustici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 18:07:02 by ljustici          #+#    #+#             */
/*   Updated: 2023/08/23 12:35:01 by ljustici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void create_threads(t_philo *philo)
{
	int i;

	i = 0;
	create_mutexes(philo);
	while(i < philo->total)
	{
		if (philo->total % 2 != 0)
		{
			if (pthread_create(&philo[i].philo, NULL, routine_odd, &philo[i]) == -1)
				printf("Error: pthread_create failed.\n");
		}
		else
		{
			if (pthread_create(&philo[i].philo, NULL, routine_even, &philo[i]) == -1)
				printf("Error: pthread_create failed.\n");
		}
		philo[i].id = i + 1;
		i++;
	}
}

void join_thread(t_philo *philo)
{
	int i;

	i = 0;
	while (i < philo->total)
	{
		pthread_join(philo[i].philo, NULL);
		printf("Philosopher [%i] has died.\n", philo[i].id);
		i++;
	}
}