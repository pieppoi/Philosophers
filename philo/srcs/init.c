/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkazuhik <mkazuhik@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 04:36:32 by mkazuhik          #+#    #+#             */
/*   Updated: 2025/10/07 16:31:59 by mkazuhik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_data(t_data *data)
{
	data->all_alive = 1;
	data->all_fed = 0;
	data->start_time = 0;
	data->philos = NULL;
	data->forks = NULL;
	data->philos = malloc(sizeof(t_philo) * data->num_philos);
	if (!data->philos)
		return (0);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philos);
	if (!data->forks)
	{
		free(data->philos);
		data->philos = NULL;
		return (0);
	}
	return (1);
}

int	init_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		data->philos[i].id = i + 1;
		data->philos[i].left_fork = i;
		data->philos[i].right_fork = (i + 1) % data->num_philos;
		data->philos[i].last_meal_time = 0;
		data->philos[i].meals_eaten = 0;
		data->philos[i].state = THINKING;
		data->philos[i].left_mutex = &data->forks[i];
		data->philos[i].right_mutex = &data->forks[(i + 1)
			% data->num_philos];
		data->philos[i].data = data;
		i++;
	}
	return (1);
}

void	cleanup(t_data *data)
{
	int	i;

	if (data->philos)
	{
		free(data->philos);
		data->philos = NULL;
	}
	if (data->forks)
	{
		i = 0;
		while (i < data->num_philos)
		{
			pthread_mutex_destroy(&data->forks[i]);
			i++;
		}
		free(data->forks);
		data->forks = NULL;
	}
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->meal_mutex);
	// pthread_cond_destroy(&data->start_cond);
	// pthread_mutex_destroy(&data->start_mutex);
}

