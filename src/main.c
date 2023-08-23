/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljustici <ljustici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 12:08:19 by ljustici          #+#    #+#             */
/*   Updated: 2023/08/23 12:52:18 by ljustici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void *routine_even(void *data)
{
	t_philo *philo = (t_philo *)data;

	if (philo->id % 2 == 0)
	{
		do_take(philo);
		do_eat(philo);
		do_sleep(philo);
		do_think(philo);
	}
	else
	{
		do_think(philo);
		do_take(philo);
		do_eat(philo);
		do_sleep(philo);
	}
	return (NULL);
}

void *routine_odd(void *data)
{
	t_philo *philo = (t_philo *)data;
	
	if (philo->id == philo->total)
	{
		do_sleep(philo);
		do_think(philo);
		do_take(philo);
		do_eat(philo);
	}
	else if (philo->id % 2 == 0)
	{
		do_take(philo);
		do_eat(philo);
		do_sleep(philo);
		do_think(philo);
	}
	else
	{
		do_think(philo);
		do_take(philo);
		do_eat(philo);
		do_sleep(philo);
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_philo *philos;
	int i;
	int n;
	
	philos = NULL;
	if (argc == 5 || argc == 6)
	{
		i = 0;
		n = ft_atoi(argv[1]);
		philos = malloc(sizeof(t_philo *));
		if (parse_args(argv, philos) == -1)
		{
			printf("Error: wrong arguments.\n");
			return (-1);
		}
		create_threads(philos);
		join_thread(philos);
	}
	return (0);
}
