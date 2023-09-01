/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljustici <ljustici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 12:08:19 by ljustici          #+#    #+#             */
/*   Updated: 2023/09/01 19:31:01 by ljustici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void *do_check(void *data)
{
	t_philo *philo = (t_philo *)data;
	
	create_threads(philo);
	while(philo->t->dead == 0 && philo->t->n_eaters < philo->t->n_times)
	{

	}
	join_thread(&philo[philo->t->dead]);
	return(NULL);
}

int	main(int argc, char **argv)
{
	t_philo *philos;
	t_table *table;
	pthread_t checker = NULL;
	pthread_mutex_t *mtx;

	philos = NULL;
	table = (t_table *)malloc(sizeof(t_table));
	mtx = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(mtx, NULL);
	if (argc == 5 || argc == 6)
	{
		philos = parse_args(argv, &table, argc, mtx);
		if (!philos)
		{
			printf("Error: wrong arguments.\n");
			return (-1);
		}
		philos->t->start = get_current_time();
		pthread_create(&checker, NULL, do_check, philos);
		//create_threads(philos);
		pthread_join(checker, NULL);
		/*while (i < (*n))
		{
			free(&philos[i]);
			i++;
		}*/
	}
	return (0);
}

