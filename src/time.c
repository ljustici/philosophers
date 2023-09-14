/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljustici <ljustici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 11:20:36 by ljustici          #+#    #+#             */
/*   Updated: 2023/09/14 18:49:46 by ljustici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long	get_routine_time(unsigned long die, unsigned long activity)
{
	unsigned long	time;

	if (activity > die)
		time = die;
	else
		time = activity;
	return (time);
}

void	set_time_left(t_philo *philo, int is_reset, unsigned long time)
{
	if (is_reset)
		philo->die_left = time;
	else if (time < philo->die_left)
		philo->die_left -= time;
	else
		philo->die_left = 0;
}

void	ft_usleep(unsigned long time)
{
	unsigned long	start;

	start = get_current_time();
	while (get_current_time() - start < time)
	{
		usleep(1000);
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
	int is_dead;

	is_dead = 0;
	if (get_current_time() - philo->die_left >= philo->die_time)
	{
		philo->is_dead = 1;
		is_dead = 1;
	}
	return (is_dead);
}
