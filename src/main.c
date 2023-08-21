/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljustici <ljustici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 12:08:19 by ljustici          #+#    #+#             */
/*   Updated: 2023/08/21 15:47:47 by ljustici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void *creating(void *data)
{
	(void) data;
	printf("Creating a thread...\n");
	return (NULL);
}

void create_threads(pthread_t *threads, int n)
{
	int i;

	i = 0;
	while(i < n)
	{	
		if (pthread_create(&threads[i], NULL, creating, NULL) == -1)
			printf("Error: pthread_create failed.\n");
		else
			printf("Created thread [%ld]\n", (long)threads[i]);
		i++;
	}
}

void join_threads(pthread_t *threads, int n)
{
	int i;

	i = 0;
	i = 0;
	while (i < n)
	{
		pthread_join(threads[i], NULL);
		printf("Main: Joining thread [%ld]\n", (long)threads[i]);
		i++;
	}
}

int	main(int argc, char **argv)
{
	pthread_t *threads = NULL;
	int i;
	int n;
	
	if (argc > 1)
	{
		i = 0;
		n = ft_atoi(argv[1]);
		threads = malloc(sizeof(pthread_t*));
		create_threads(threads, n);
		join_threads(threads, n);
	}
	return (0);
}
