/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljustici <ljustici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 12:08:19 by ljustici          #+#    #+#             */
/*   Updated: 2023/08/21 18:11:31 by ljustici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void *creating(void *data)
{
	(void) data;
	printf("Creating a thread...\n");
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_philo *philos = NULL;
	pthread_mutex_t *forks = NULL;
	int i;
	int n;
	
	if (argc > 1)
	{
		i = 0;
		n = ft_atoi(argv[1]);
		philos = malloc(sizeof(t_philo *));
		create_threads(&philos->philo, n);
		join_threads(&philos->philo, n);
	}
	return (0);
}
