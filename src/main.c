/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljustici <ljustici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 12:08:19 by ljustici          #+#    #+#             */
/*   Updated: 2023/09/16 16:27:57 by ljustici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*do_check(void *data)
{
	t_philo	*philo;
	int		dead;
	int		all_ate;

	philo = (t_philo *)data;
	dead = 0;
	create_threads(philo);
	while (all_created(philo) == 0)
		usleep(40);
	while (1)
	{
		dead = is_there_dead(philo);
		all_ate = did_all_eat(philo);
		if (all_ate)
			break ;
		if (dead)
		{
			report_action("died", philo[dead - 1]);
			break ;
		}
	}
	join_threads(philo);
	destroy_mutexes(philo);
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
			free(table);
			write(2, "Error: wrong arguments.\n", 24);
			return (-1);
		}
		if (pthread_create(&checker, NULL, do_check, philos) == 0)
			pthread_join(checker, NULL);
	}
	free_philos(philos);
	free(table);
	return (0);
}

/*
atexit(ft_leaks);

void ft_leaks()
{
	system("leaks -q --fullContent   philo");
}

en CFLAGS #-fsanitize=thread -g
*/