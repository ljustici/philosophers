/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljustici <ljustici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 12:08:19 by ljustici          #+#    #+#             */
/*   Updated: 2023/09/10 17:13:00 by ljustici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void report_action(char *msg, t_philo philo)
{
    pthread_mutex_lock(philo.t->mtx_print);
    printf("[%lu] %i %s\n", get_current_time() - philo.start, philo.id, msg);
    pthread_mutex_unlock(philo.t->mtx_print);
}

void	*do_check(void *data)
{
	t_philo	*philo = (t_philo *)data;
	int		n;
	int		dead;

	dead = 0;
	n = philo->t->n_times;
	create_threads(philo);
	while(1)
	{
		dead = is_there_dead(philo);
		if (dead)
		{
			report_action("died.", philo[dead - 1]);
			break;
		}
		pthread_mutex_lock(philo->t->mtx_nt);
		if (n == philo->t->n_eaters)
		{
			pthread_mutex_unlock(philo->t->mtx_nt);
			break;
		}
		pthread_mutex_unlock(philo->t->mtx_nt);
	}
	join_threads(philo);
	//destroy_mutexes(philo);
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_philo		*philos;
	t_table		*table;
	pthread_t	checker;

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
	}
	//free(table);
	return (0);
}
