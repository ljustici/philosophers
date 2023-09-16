/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljustici <ljustici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 11:20:36 by ljustici          #+#    #+#             */
/*   Updated: 2023/09/16 18:20:57 by ljustici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	should_philo_die(t_philo *philo, unsigned long activity)
{
	unsigned long	last_eat;
	int				should_die;

	should_die = 0;
	last_eat = get_t_last_eat(philo);
	if (last_eat + activity >= philo->die_time)
		should_die = 1;
	return (should_die);
}

void	ft_usleep(unsigned long time)
{
	unsigned long	start;

	start = get_current_time();
	while (get_current_time() - start < time)
	{
		usleep(50);
	}
}

unsigned long	get_current_time(void)
{
	struct timeval	current_us;

	gettimeofday(&current_us, NULL);
	return (current_us.tv_sec * 1000 + current_us.tv_usec / 1000);
}

int	time_last_eat(t_philo *philo)
{
	int	is_dead;

	is_dead = 0;
	if (get_t_last_eat(philo) >= philo->die_time)
	{
		philo->is_dead = 1;
		is_dead = 1;
	}
	return (is_dead);
}

unsigned long	get_t_last_eat(t_philo *philo)
{
	return (get_current_time() - philo->die_left);
}
