/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkazuhik <mkazuhik@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 03:31:43 by mkazuhik          #+#    #+#             */
/*   Updated: 2025/10/01 04:53:56 by mkazuhik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	cleanup_forks(t_data *data, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	free(data->forks);
	free(data->philos);
}

int	init_fork_mutexes(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
		{
			cleanup_forks(data, i);
			return (0);
		}
		i++;
	}
	return (1);
}

int	init_other_mutexes(t_data *data)
{
	if (pthread_mutex_init(&data->print_mutex, NULL) != 0)
	{
		cleanup_forks(data, data->num_philos);
		return (0);
	}
	if (pthread_mutex_init(&data->meal_mutex, NULL) != 0)
	{
		pthread_mutex_destroy(&data->print_mutex);
		cleanup_forks(data, data->num_philos);
		return (0);
	}
    if (pthread_mutex_init(&data->start_mutex, NULL) != 0)
    {
        pthread_mutex_destroy(&data->meal_mutex);
        pthread_mutex_destroy(&data->print_mutex);
        cleanup_forks(data, data->num_philos);
        return (0);
    }
    if (pthread_cond_init(&data->start_cond, NULL) != 0)
    {
        pthread_mutex_destroy(&data->start_mutex);
        pthread_mutex_destroy(&data->meal_mutex);
        pthread_mutex_destroy(&data->print_mutex);
        cleanup_forks(data, data->num_philos);
        return (0);
    }
    data->started = 0;
	return (1);
}

int	init_mutexes(t_data *data)
{
	if (!init_fork_mutexes(data))
		return (0);
	if (!init_other_mutexes(data))
		return (0);
	return (1);
}
