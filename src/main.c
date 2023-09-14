/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljustici <ljustici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 12:08:19 by ljustici          #+#    #+#             */
/*   Updated: 2023/09/14 15:53:08 by ljustici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	report_action(char *msg, t_philo philo)
{
	pthread_mutex_lock(philo.t->mtx_print);
	printf("%lu %i %s\n", get_current_time() - philo.t->start, philo.id, msg);
	pthread_mutex_unlock(philo.t->mtx_print);
}

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
			write(2, "Error: wrong arguments.\n", 24);
			return (-1);
		}
		pthread_create(&checker, NULL, do_check, philos);
		pthread_join(checker, NULL);
	}
	free_philos(philos);
	free(table);
	return (0);
}

void	free_philos(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->t->total)
	{
		free(&philo[i]);
		i++;
	}
}

void	set_stop(t_philo *philo, int all_ate)
{
	if (all_ate)
		return ;
	else
	{
		pthread_mutex_lock(philo->t->mtx_check);
		philo->t->dead = philo->id;
		pthread_mutex_unlock(philo->t->mtx_check);
	}
}
