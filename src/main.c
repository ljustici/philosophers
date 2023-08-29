/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljustici <ljustici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 12:08:19 by ljustici          #+#    #+#             */
/*   Updated: 2023/08/29 17:04:46 by ljustici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void *routine(void *data)
{
	t_philo *philo = (t_philo *)data;

	while (philo->die_left > 0)
	{
		if (*(philo->total) % 2 != 0 && philo->id == *(philo->total))
		{
			
			do_sleep(philo);
			printf("Aqui 2\n");
			//do_think(philo);
			//do_eat(philo);
		}
		else if (philo->id % 2 == 0)
		{
			//do_eat(philo);
			do_sleep(philo);
			//do_think(philo);
		}
		else
		{
			//do_think(philo);
			//do_eat(philo);
			do_sleep(philo);
		}
	}
	philo->is_dead = 1;
	printf("[%lu] Philosopher [%i] has died.\n", get_current_time(), philo->id);
	return (&philo->id);
}

void *do_report(void *data)
{
	t_philo *philo = (t_philo *)data;
	int i;

	i = 1;
	create_threads(philo);
	/*while(1)
	{
		if (philo[i].is_dead)
		{
			*(philo->total) = 0;
			break;
		}
	}*/
	//join_thread(&philo[i]);
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
		philos = NULL;
		n = malloc(sizeof(int *));
		if (parse_args(argv, &philos, &n) == -1)
		{
			printf("Error: wrong arguments.\n");
			return (-1);
		}
		//printf("%i", *(philos[0].total));
		pthread_create(&reporter, NULL, do_report, philos);
		//create_threads(philos);
		pthread_join(reporter, NULL);
		free(n);
		//free(philos);
	}
	return (0);
}

