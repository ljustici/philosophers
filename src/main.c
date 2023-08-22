/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljustici <ljustici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 12:08:19 by ljustici          #+#    #+#             */
/*   Updated: 2023/08/22 16:42:59 by ljustici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void *routine(void *data)
{
	t_philo *philo = (t_philo *)data;
	
	if (philo->total % 2 == 0)
	{
		do_take(philo);
		do_eat(philo);
	//do_sleep(*philo);
	//do_think(*philo);
	}
	else
	{
		do_sleep(philo);
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_philo *philos = NULL;
	int i;
	int n;
	
	if (argc > 1)
	{
		i = 0;
		n = ft_atoi(argv[1]);
		philos = malloc(sizeof(t_philo *));
		create_threads(philos, n);
		join_threads(philos, n);
	}
	return (0);
}
