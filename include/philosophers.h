/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljustici <ljustici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 12:17:19 by ljustici          #+#    #+#             */
/*   Updated: 2023/08/21 17:41:11 by ljustici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS
# define PHILOSOPHERS

# include <string.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>

typedef struct s_philo
{
	pthread_t	philo;
	int			id;
}	t_philo;

int	ft_atoi(const char *str);

#endif