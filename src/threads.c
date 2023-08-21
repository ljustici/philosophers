/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljustici <ljustici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 18:07:02 by ljustici          #+#    #+#             */
/*   Updated: 2023/08/21 18:07:50 by ljustici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void create_threads(pthread_t *threads, int n)
{
	int i;

	i = 0;
	while(i < n)
	{
		if (pthread_create(&threads[i], NULL, creating, NULL) == -1)
			printf("Error: pthread_create failed.\n");
		else
		{
			printf("Created thread [%ld]\n", (long)threads[i]);
		}
		i++;
	}
}

void join_threads(pthread_t *threads, int n)
{
	int i;

	i = 0;
	while (i < n)
	{
		pthread_join(threads[i], NULL);
		printf("Main: Joining thread [%ld]\n", (long)threads[i]);
		i++;
	}
}