/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljustici <ljustici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 15:47:37 by ljustici          #+#    #+#             */
/*   Updated: 2023/09/10 16:46:29 by ljustici         ###   ########.fr       */
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

t_philo	*parse_args(char **argv, t_table **table, int argc)
{
	int		i;
	t_philo	*philo;
	
	i = 0;
	(*table)->total = ft_atoi(argv[1]);
	(*table)->dead = 0;
	if ((*table)->total == 0)
		return (NULL);
	philo = malloc(sizeof(t_philo) * ((*table)->total));
	if (!philo)
		return (NULL);
	create_mutexes(table, philo);
	while (i < (*table)->total)
	{
		philo[i].fork_right = 0;
		philo[i].id = i + 1;
		philo[i].is_dead = 0;
		philo[i].n_eaten = 0;
		philo[i].die_time = ft_atoi(argv[2]);
		philo[i].eat_time = ft_atoi(argv[3]);
		philo[i].sleep_time = ft_atoi(argv[4]);
		philo[i].die_left = philo[i].die_time;
		philo[i].t = *table;
		i++;
	}
	if (argc == 6)
		(*table)->n_times = ft_atoi(argv[5]);
	else
		(*table)->n_times = -1;
	if (philo[i - 1].die_time == 0 || philo[i - 1].eat_time
		== 0 || philo[i - 1].sleep_time == 0 || (*table)->n_times == 0)
			return (NULL);
	return (philo);
}

void	set_forks(t_philo *philo)
{
	int	i;
	int	n;

	i = 0;
	n = philo->t->total;
	i = 0;
	while(i < n && n > 1)
	{
		if (i == n - 1)
			philo[i].fork_left = &philo[0].fork_right;
		else
			philo[i].fork_left = &philo[i + 1].fork_right;
		i++;
	}
}
