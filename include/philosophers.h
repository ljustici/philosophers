/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljustici <ljustici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 12:17:19 by ljustici          #+#    #+#             */
/*   Updated: 2023/08/22 15:58:58 by ljustici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS
# define PHILOSOPHERS

# include <string.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_philo
{
	pthread_t	philo;
	int			id;
	unsigned long	eat_time;
	unsigned long	die_time;
	unsigned long	sleep_time;
	pthread_mutex_t fork_right;
	pthread_mutex_t *fork_left;
}	t_philo;

int	ft_atoi(const char *str);

void *routine(void *data);
void do_take(t_philo *philo);
void do_eat(t_philo *philo);
void do_sleep(t_philo philo);
void do_think(t_philo philo);

void create_threads(t_philo *philo, int n);
void join_threads(t_philo *philo, int n);

void create_mutexes(t_philo *philo, int n);
void destroy_mutexes(pthread_mutex_t *mutexes, int n);

#endif