/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutexes.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljustici <ljustici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 18:07:37 by ljustici          #+#    #+#             */
/*   Updated: 2023/08/21 18:10:14 by ljustici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void create_mutexes(pthread_mutex_t *mutexes, int n)
{
	int i;

	i = 0;
	while(i < n)
	{
		if (pthread_mutex_init(&mutexes[i], NULL) == -1)
			printf("Error: pthread_mutex_init failed.\n");
		i++;
	}
}

void destroy_mutexes(pthread_mutex_t *mutexes, int n)
{
	int i;

	i = 0;
	while(i < n)
	{
		if (pthread_mutex_destroy(&mutexes[i]) == -1)
			printf("Error: pthread_mutex_destroy failed.\n");
		i++;
	}
}