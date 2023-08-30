/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljustici <ljustici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 12:08:19 by ljustici          #+#    #+#             */
/*   Updated: 2023/08/30 17:59:43 by ljustici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void *routine(void *data)
{
	t_philo *philo = (t_philo *)data;
	int n;
	
	philo->start = get_current_time();
	n = *(philo->total);
	while (philo->is_dead == 0)
	{
		do_eat(philo);
		do_sleep(philo);
		do_think(philo);
		/*if (*(philo->total) % 2 != 0 && philo->id == n)
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
		}*/
	}
	return (&philo->id);
}

void *do_report(void *data)
{
	t_philo *philo = (t_philo *)data;
	
	create_threads(philo);
	/*while(*(philo->total) != 0)
	{
		
	}*/
	join_thread(philo);
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
		n = malloc(sizeof(int *));
		philos = parse_args(argv, &n);
		if (!philos)
		{
			printf("Error: wrong arguments.\n");
			return (-1);
		}
		pthread_create(&reporter, NULL, do_report, philos);
		//create_threads(philos);
		pthread_join(reporter, NULL);
		free(n);
		i = 0;
		/*while (i < (*n))
		{
			free(&philos[i]);
			i++;
		}*/
	}
	return (0);
}

