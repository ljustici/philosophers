/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljustici <ljustici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 12:08:19 by ljustici          #+#    #+#             */
/*   Updated: 2023/08/31 17:13:15 by ljustici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void *routine(void *data)
{
	t_philo *philo = (t_philo *)data;
	int n;
	
	n = 0;
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

void *do_check(void *data)
{
	t_philo *philo = (t_philo *)data;
	
	create_threads(philo);
	while(philo->t->dead == 0)
	{
		
	}
	join_thread(&philo[philo->t->dead]);
	return(NULL);
}

int	main(int argc, char **argv)
{
	t_philo *philos;
	t_table *table;
	int *n;
	pthread_t checker = NULL;

	philos = NULL;
	table = (t_table *)malloc(sizeof(t_table));
	if (argc == 5 || argc == 6)
	{
		n = malloc(sizeof(int *));
		philos = parse_args(argv, &table);
		if (!philos)
		{
			printf("Error: wrong arguments.\n");
			return (-1);
		}
		philos->t->start = get_current_time();
		printf("total: %i, die: %lu", philos->t->total, philos[1].die_time);
		pthread_create(&checker, NULL, do_check, philos);
		//create_threads(philos);
		pthread_join(checker, NULL);
		free(n);
		/*while (i < (*n))
		{
			free(&philos[i]);
			i++;
		}*/
	}
	return (0);
}

