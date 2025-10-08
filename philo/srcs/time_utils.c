/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                      :+:      :+:    :+:   */
/*                                                    ft +:+         +:+     */
/*   By: mkazuhik <mkazuhik@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 03:32:09 by mkazuhik          #+#    #+#             */
/*   Updated: 2025/10/09 01:00:00 by mkazuhik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(void)
{
	struct timeval	tv;
	long			time_in_ms;

	gettimeofday(&tv, NULL);
	time_in_ms = tv.tv_sec * 1000 + (tv.tv_usec + 500) / 1000;
	return (time_in_ms);
}

long	get_time_microseconds(void)
{
	struct timeval	tv;
	long			time_in_us;

	gettimeofday(&tv, NULL);
	time_in_us = tv.tv_sec * 1000000 + tv.tv_usec;
	return (time_in_us);
}

void	precise_usleep(long microseconds)
{
	long	start_time;
	long	current_time;

	start_time = get_time_microseconds();
	while (1)
	{
		current_time = get_time_microseconds();
		if (current_time - start_time >= microseconds)
			break ;
		usleep(50);
	}
}
