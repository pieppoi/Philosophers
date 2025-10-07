/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkazuhik <mkazuhik@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 03:32:09 by mkazuhik          #+#    #+#             */
/*   Updated: 2025/10/08 05:28:21 by mkazuhik         ###   ########.fr       */
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

void	precise_usleep(long microseconds)
{
	long	start_time;
	long	current_time;

	start_time = get_time() * 1000;
	while (1)
	{
		current_time = get_time() * 1000;
		if (current_time - start_time >= microseconds)
			break ;
		usleep(100);
	}
}

void	print_status(t_philo *philo, const char *status)
{
	long		timestamp;

	pthread_mutex_lock(&philo->data->print_mutex);
	pthread_mutex_lock(&philo->data->meal_mutex);
	if (philo->data->all_alive && !philo->data->all_fed)
	{
		timestamp = get_time() - philo->data->start_time;
		printf("%ld %d %s\n", timestamp, philo->id, status);
	}
	pthread_mutex_unlock(&philo->data->meal_mutex);
	pthread_mutex_unlock(&philo->data->print_mutex);
}

int	check_death(t_philo *philo)
{
	long	current_time;
	long	time_since_last_meal;

	pthread_mutex_lock(&philo->data->meal_mutex);
	current_time = get_time();
	time_since_last_meal = current_time - philo->last_meal_time;
	if (time_since_last_meal >= philo->data->time_to_die
		&& philo->data->all_alive)
	{
		philo->data->all_alive = 0;
		pthread_mutex_unlock(&philo->data->meal_mutex);
		pthread_mutex_lock(&philo->data->print_mutex);
		printf("%ld %d died\n", current_time - philo->data->start_time,
			philo->id);
		pthread_mutex_unlock(&philo->data->print_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->meal_mutex);
	return (0);
}

int	error_exit(const char *message)
{
	printf("Error: %s\n", message);
	return (1);
}
