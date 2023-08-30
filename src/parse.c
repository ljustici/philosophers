/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljustici <ljustici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 15:47:37 by ljustici          #+#    #+#             */
/*   Updated: 2023/08/30 13:07:33 by ljustici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	minus;
	int	number;

	number = 0;
	i = 0;
	minus = 1;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
	{
		i++;
	}
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			minus = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		number = number * 10 + (str[i] - '0');
		i++;
	}
	return (number * minus);
}

t_philo	*parse_args(char **argv, int **n)
{
	int	i;
	t_philo *philo;
	
	i = 0;
	**n = ft_atoi(argv[1]);
	if (**n == 0)
		return (NULL);
	philo = malloc(sizeof(t_philo) * (**n));
	while (i < (**n))
	{
		philo[i].fork_right = 0;
		philo[i].id = i + 1;
		philo[i].total = *n;
		philo[i].die_time = get_us(ft_atoi(argv[2]));
		philo[i].eat_time = get_us(ft_atoi(argv[3]));
		philo[i].sleep_time = get_us(ft_atoi(argv[4]));
		philo[i].die_left = philo[i].die_time;
		philo[i].fork_right = 0;
		philo[i].is_dead = 0;
		i++;
	}
	
	if (philo[i - 1].die_time == 0 || philo[i - 1].eat_time
		== 0 || philo[i - 1].sleep_time == 0)
			return (NULL);
	return (philo);
}

unsigned long get_ms(suseconds_t usecs)
{
	return (usecs/1000);
}

unsigned long get_us(unsigned long ms)
{
	return (ms*1000);
}

unsigned long	get_current_time()
{
	unsigned long current_ms;
	struct timeval current_us;
	
	gettimeofday(&current_us, NULL);
	current_ms = get_ms(current_us.tv_usec);
	return(current_us.tv_sec + current_ms);
}