/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljustici <ljustici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 12:08:19 by ljustici          #+#    #+#             */
/*   Updated: 2023/08/28 16:49:30 by ljustici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void *routine(void *data)
{
	t_philo *philo = (t_philo *)data;
	struct timeval current_us;
    unsigned long current_ms;

	gettimeofday(&current_us, NULL);
    current_ms = get_ms(current_us.tv_usec);
	while (philo->die_left > 0 && philo->total != 0)
	{
		if (*(philo->total) % 2 != 0 && philo->id == *(philo->total))
		{
			do_sleep(philo);
			do_think(philo);
			do_eat(philo);
		}
		else if (philo->id % 2 == 0)
		{
			do_eat(philo);
			do_sleep(philo);
			do_think(philo);
		}
		else
		{
			do_think(philo);
			do_eat(philo);
			do_sleep(philo);
		}
	}
	philo->is_dead = 1;
	printf("[%lu] Philosopher [%i] has died.\n", current_ms, philo->id);
	return (&philo->id);
}

void *do_report(void *data)
{
	t_philo *philo = (t_philo *)data;
	int i;

	i = 1;
	create_threads(philo);
	while(1)
	{
		if (philo[i].is_dead)
			break;
	}
	join_thread(&philo[i]);
	return(NULL);
}

int	main(int argc, char **argv)
{
	t_philo *philos;
	int i;
	int *n;
	pthread_t reporter = NULL;

	philos = NULL;
	if (argc == 5 || argc == 6)
	{
		i = 0;
		philos = malloc(sizeof(t_philo *));
		n = malloc(sizeof(int *));
		if (parse_args(argv, philos, n) == -1)
		{
			printf("Error: wrong arguments.\n");
			return (-1);
		}
		pthread_create(&reporter, NULL, do_report, philos);
		//create_threads(philos);
		pthread_join(reporter, NULL);
	}
	return (0);
}

