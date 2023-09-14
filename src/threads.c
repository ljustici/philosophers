/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljustici <ljustici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 18:07:02 by ljustici          #+#    #+#             */
/*   Updated: 2023/09/14 15:53:31 by ljustici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	create_threads(t_philo *philo)
{
	int	i;

	i = 0;
	set_forks(philo);
	while (i < philo->t->total)
	{
		if (pthread_create(&philo[i].philo, NULL, routine, &philo[i]) == -1)
			printf("Error: pthread_create failed.\n");
		usleep(100);
		i++;
	}
}

void	join_thread(t_philo *philo)
{
	void	*rvalue;

	rvalue = NULL;
	pthread_join(philo->philo, &rvalue);
}

void	join_threads(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->t->total)
	{
		pthread_join(philo[i].philo, NULL);
		i++;
	}
}

int	all_created(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->t->total)
	{
		if (philo->philo)
			i++;
	}
	if (i == philo->t->total)
	{
		pthread_mutex_lock(philo->t->mtx_print);
		philo->t->start = get_current_time();
		pthread_mutex_unlock(philo->t->mtx_print);
		return (1);
	}
	return (0);
}

int	is_there_start(t_philo *philo)
{
	int	start;

	start = 0;
	pthread_mutex_lock(philo->t->mtx_print);
	if (philo->t->start == 0)
		start = 0;
	else
		start = 1;
	pthread_mutex_unlock(philo->t->mtx_print);
	return (start);
}
