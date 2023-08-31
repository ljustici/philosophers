/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljustici <ljustici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 17:21:57 by ljustici          #+#    #+#             */
/*   Updated: 2023/08/31 17:34:53 by ljustici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void report_action(char *msg, t_philo philo)
{
    pthread_mutex_t *mtx_print;

    mtx_print = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t));
    pthread_mutex_init(mtx_print, NULL);
    pthread_mutex_lock(mtx_print);
    printf("[%lu] %i %s\n", get_current_time() - philo.t->start, philo.id, msg);
    pthread_mutex_unlock(mtx_print);
    pthread_mutex_destroy(mtx_print);
}

void set_death(t_philo *philo)
{
    pthread_mutex_t *mtx_print;

    mtx_print = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t));
    pthread_mutex_init(mtx_print, NULL);
    pthread_mutex_lock(mtx_print);
    philo->t->dead = philo->id;
    philo->is_dead = 1;
    printf("[%lu] Philosopher %i is dead. time left: %lu\n", get_current_time() - philo->t->start, philo->id, philo->die_left);
    pthread_mutex_unlock(mtx_print);
    pthread_mutex_destroy(mtx_print);
}