/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljustici <ljustici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 15:47:37 by ljustici          #+#    #+#             */
/*   Updated: 2023/08/31 17:16:43 by ljustici         ###   ########.fr       */
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

t_philo	*parse_args(char **argv, t_table **table)
{
	int	i;
	t_philo *philo;
	
	i = 0;
	(*table)->total = ft_atoi(argv[1]);
	
	(*table)->dead = 0;
	if ((*table)->total == 0)
		return (NULL);
	philo = malloc(sizeof(t_philo) * ((*table)->total));
	if (!philo)
		return (NULL);
	while (i < (*table)->total)
	{
		philo[i].fork_right = 0;
		philo[i].id = i + 1;
		philo[i].is_dead = 0;
		philo[i].n_times = 0;
		philo[i].die_time = ft_atoi(argv[2]);
		philo[i].eat_time = ft_atoi(argv[3]);
		philo[i].sleep_time = ft_atoi(argv[4]);
		philo[i].die_left = philo[i].die_time;
		philo[i].t = *table;
		i++;
	}
	if (philo[i - 1].die_time == 0 || philo[i - 1].eat_time
		== 0 || philo[i - 1].sleep_time == 0)
			return (NULL);
	return (philo);
}

