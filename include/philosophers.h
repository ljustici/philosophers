/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljustici <ljustici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 12:17:19 by ljustici          #+#    #+#             */
/*   Updated: 2023/09/01 19:33:06 by ljustici         ###   ########.fr       */
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

typedef struct s_table
{
	unsigned long	start;
	int				total;
	int				dead;
	int				n_times;
	int				n_eaters;
	pthread_mutex_t	*mtx;
}	t_table;

typedef struct s_philo
{
	pthread_t		philo;
	int				id;
	int				is_dead;
	int				n_eaten;
	unsigned long	eat_time;
	unsigned long	die_time;
	unsigned long	sleep_time;
	unsigned long	die_left;
	int				fork_right;
	int				*fork_left;
	t_table			*t;
}	t_philo;

int				ft_atoi(const char *str);
t_philo			*parse_args(char **argv, t_table **table, int argc, pthread_mutex_t *mtx);

unsigned long	get_routine_time(unsigned long die, unsigned long activity);
unsigned long	get_ms(suseconds_t usecs);
unsigned long	get_us(unsigned long ms);
unsigned long	get_current_time();
void			set_time_left(unsigned long *die, unsigned long new);
int 			do_try_fork(t_philo *philo, unsigned long time);
void			ft_usleep(unsigned long time);

void			*routine(void *data);
void			do_take(t_philo *philo);
void			do_eat(t_philo *philo);
void			do_sleep(t_philo *philo);
void			do_think(t_philo *philo);
int set_if_death(t_philo *philo, unsigned long activity);
void report_action(char *msg, t_philo philo);
int take_right_fork(t_philo *philo);
void release_forks(t_philo *philo);
int check_cond(t_philo *philo);

void			create_threads(t_philo *philo);
void			join_thread(t_philo *philo);

void			set_forks(t_philo *philo);
void			destroy_mutexes(pthread_mutex_t *mutexes, int n);

#endif