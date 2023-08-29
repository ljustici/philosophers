/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljustici <ljustici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 12:17:19 by ljustici          #+#    #+#             */
/*   Updated: 2023/08/29 15:31:27 by ljustici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS
# define PHILOSOPHERS

# include <string.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

# define NC	"\e[0m"
# define YELLOW	"\e[1;33m"

typedef struct s_philo
{
	pthread_t		philo;
	int				id;
	int				*total;
	int				is_dead;
	unsigned long	eat_time;
	unsigned long	die_time;
	unsigned long	sleep_time;
	unsigned long	die_left;
	int	fork_right;
	int	*fork_left;
}	t_philo;

int				ft_atoi(const char *str);
int				parse_args(char **argv, t_philo **philo, int **n);
unsigned long	get_ms(suseconds_t usecs);
unsigned long	get_us(unsigned long ms);
unsigned long	get_current_time();

void			*routine(void *data);
void			do_take(t_philo *philo);
void			do_eat(t_philo *philo);
void			do_sleep(t_philo *philo);
void			do_think(t_philo *philo);

void			create_threads(t_philo *philo);
void			join_thread(t_philo *philo);

void			set_forks(t_philo *philo);
void			destroy_mutexes(pthread_mutex_t *mutexes, int n);

#endif