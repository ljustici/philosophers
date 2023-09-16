/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljustici <ljustici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 15:47:37 by ljustici          #+#    #+#             */
/*   Updated: 2023/09/16 17:25:14 by ljustici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

long	ft_atoi(const char *str)
{
	int		i;
	long	number;

	number = 0;
	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		number = number * 10 + (str[i] - '0');
		i++;
	}
	if (number >= 2147483647)
		return (0);
	return (number);
}

int	are_args_parseable(int n, char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (i < n)
	{
		j = 0;
		if (ft_strlen(argv[i]) == 0 || (ft_strlen(argv[i]) == 1
				&& (argv[i][j] == '+' || argv[i][j] == '-')))
			return (-1);
		while (j < ft_strlen(argv[i]))
		{
			if ((j == 0 && argv[i][j] == '-') || (j == 0 && argv[i][j] == '+'))
				j++;
			else if (!(argv[i][j] >= '0' && argv[i][j] <= '9'))
				return (-1);
			else
				j++;
		}
		i++;
	}
	return (0);
}

t_philo	*init_philo(char **argv, t_table **table)
{
	t_philo	*philo;
	int		i;

	i = 0;
	philo = malloc(sizeof(t_philo) * ((*table)->total));
	if (!philo)
		return (NULL);
	if (create_mutexes(table, philo) != 0)
		return (free(philo), NULL);
	while (i < (*table)->total)
	{
		philo[i].fork_right = 0;
		philo[i].id = i + 1;
		philo[i].is_dead = 0;
		philo[i].start = 0;
		philo[i].n_eaten = 0;
		philo[i].die_time = ft_atoi(argv[2]);
		philo[i].eat_time = ft_atoi(argv[3]);
		philo[i].sleep_time = ft_atoi(argv[4]);
		philo[i].die_left = philo[i].die_time;
		philo[i].t = *table;
		i++;
	}
	return (philo);
}

t_philo	*parse_args(char **argv, t_table **table, int argc)
{
	int		i;
	t_philo	*philo;

	i = 0;
	if (are_args_parseable(argc, argv) == -1)
		return (NULL);
	(*table)->total = ft_atoi(argv[1]);
	(*table)->dead = 0;
	(*table)->start = 0;
	if ((*table)->total == 0)
		return (NULL);
	philo = init_philo(argv, table);
	if (!philo)
		return (NULL);
	if (argc == 6)
		(*table)->n_times = ft_atoi(argv[5]);
	else
		(*table)->n_times = -1;
	if (philo->die_time == 0 || philo->eat_time
		== 0 || philo->sleep_time == 0 || (*table)->n_times == 0)
		return (NULL);
	return (philo);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
