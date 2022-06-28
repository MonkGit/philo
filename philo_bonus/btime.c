/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btime.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slaree <slaree@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 21:30:56 by slaree            #+#    #+#             */
/*   Updated: 2022/06/28 21:31:19 by slaree           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bphilo.h"

long long	get_time_now(void)
{
	t_timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

void	isleep(long long ms)
{
	long long	time_now;

	time_now = get_time_now();
	while (get_time_now() < (time_now + ms))
		usleep(10);
}

long long	time_to_long(t_timeval t)
{
	return (t.tv_sec * 1000 + t.tv_usec / 1000);
}
