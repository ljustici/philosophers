/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljustici <ljustici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 12:08:19 by ljustici          #+#    #+#             */
/*   Updated: 2023/09/02 15:30:34 by ljustici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void *do_check(void *data)
{
	t_philo *philo = (t_philo *)data;
	int i;
	int n;
	
	i = 0;
	n = philo->t->n_times;
	create_threads(philo);
	while(1)
	{
		if (philo->t->dead)
			break;
		if (n == philo->t->n_eaters)
			break;
		if (i == philo->t->total - 1)
			i = 0;
		i++;
	}
	join_thread(&philo[philo->t->dead]);
	join_threads(philo);
	return(NULL);
}

int	main(int argc, char **argv)
{
	t_philo *philos;
	t_table *table;
	pthread_t checker;
	int i = 0;

	checker = NULL;
	philos = NULL;
	table = (t_table *)malloc(sizeof(t_table));
	if (argc == 5 || argc == 6)
	{
		philos = parse_args(argv, &table, argc);
		if (!philos)
		{
			printf("Error: wrong arguments.\n");
			return (-1);
		}
		philos->t->start = get_current_time();
		pthread_create(&checker, NULL, do_check, philos);
		pthread_join(checker, NULL);
		while (i < philos->t->total)
		{
			free(&philos[i]);
			i++;
		}
	}
	return (0);
}
