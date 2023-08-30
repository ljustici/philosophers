/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljustici <ljustici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 11:20:36 by ljustici          #+#    #+#             */
/*   Updated: 2023/08/30 14:42:15 by ljustici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

unsigned long get_routine_time(unsigned long die, unsigned long activity)
{
    unsigned long time;

    if (activity > die)
        time = activity - die;
    else
        time = activity;
    return (time);
}

int is_dead(unsigned long die_left, unsigned long activity)
{
    int is_dead;

    is_dead = 0;
    if (activity > die_left)
        is_dead = 1;
    return (is_dead);
}

void time_left(unsigned long *die, unsigned long new)
{
    *die = new;
}

void is_fork_taken(int *fork, int is_taken)
{
    if (is_taken)
        *fork = 1;
    else
        *fork = 0;
}