/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljustici <ljustici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 12:08:19 by ljustici          #+#    #+#             */
/*   Updated: 2023/09/09 17:20:07 by ljustici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void *do_check(void *data)
{
	t_philo *philo = (t_philo *)data;
	int n;
	
	n = philo->t->n_times;
	philo->t->start = get_current_time();
	create_threads(philo);
	while(1)
	{
		if (is_there_dead(philo)) 
			break;
		pthread_mutex_lock(philo->t->mtx_nt);
		if (n == philo->t->n_eaters)
		{
			pthread_mutex_unlock(philo->t->mtx_nt);
			break;
		}
		pthread_mutex_unlock(philo->t->mtx_nt);
	}
	join_thread(&philo[0]);
	join_threads(philo);
	return(NULL);
}

int	main(int argc, char **argv)
{
	t_philo *philos;
	t_table *table;
	pthread_t checker;
	//int i = 0;

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
		pthread_create(&checker, NULL, do_check, philos);
		
		pthread_join(checker, NULL);
		/*while (i < philos->t->total)
		{
			free(&philos[i]);
			i++;
		}*/
	}
	return (0);
}
