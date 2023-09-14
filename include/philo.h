/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljustici <ljustici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 12:17:19 by ljustici          #+#    #+#             */
/*   Updated: 2023/09/14 18:49:54 by ljustici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

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
	pthread_mutex_t	*mtx_print;
	pthread_mutex_t	*mtx_nt;
	pthread_mutex_t	*mtx_cond;
	pthread_mutex_t	*mtx_check;
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
	unsigned long	start;
	int				fork_right;
	int				*fork_left;
	pthread_mutex_t	*mtx_fork_r;
	pthread_mutex_t	*mtx_fork_l;
	t_table			*t;
}	t_philo;

int				ft_atoi(const char *str);
t_philo			*parse_args(char **argv, t_table **table, int argc);
void			set_forks(t_philo *philo);

unsigned long	get_routine_time(unsigned long die, unsigned long activity);
unsigned long	get_current_time(void);
void			set_time_left(t_philo *philo, int is_reset, unsigned long time);
void			ft_usleep(unsigned long time);

int				did_all_eat(t_philo *philo);
int				grab_forks(t_philo *philo);
void			release_forks(t_philo *philo);
int				do_try_fork(t_philo *philo, unsigned long time);

void			*routine(void *data);
void			do_take(t_philo *philo);
void			do_eat(t_philo *philo);
void			do_sleep(t_philo *philo);
void			do_think(t_philo *philo);

void			set_if_death(t_philo *philo);
void			report_action(char *msg, t_philo philo);
int				check_cond(t_philo *philo);
void			set_stop(t_philo *philo, int all_ate);
int				is_there_dead(t_philo *philo);
void			set_eater(t_philo *philo);

void			create_threads(t_philo *philo);
void			join_threads(t_philo *philo);
void			create_mutexes(t_table **table, t_philo *philo);
void			destroy_mutexes(t_philo *philo);

int				all_created(t_philo *philo);
int				is_there_start(t_philo *philo);

void			free_philos(t_philo *philo);

int				time_last_eat(t_philo *philo);

#endif