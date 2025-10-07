/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkazuhik <mkazuhik@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 04:36:32 by mkazuhik          #+#    #+#             */
/*   Updated: 2025/10/08 05:28:02 by mkazuhik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_philosopher_deaths(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		if (check_death(&data->philos[i]))
			return (1);
		i++;
	}
	return (0);
}

void	monitor_philosophers(t_data *data)
{
	while (1)
	{
		usleep(5000);
		pthread_mutex_lock(&data->meal_mutex);
		if (!data->all_alive)
		{
			pthread_mutex_unlock(&data->meal_mutex);
			break ;
		}
		pthread_mutex_unlock(&data->meal_mutex);
		if (check_philosopher_deaths(data))
			break ;
		if (check_all_fed(data))
			break ;
	}
}

void	wait_for_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		pthread_join(data->philos[i].thread, NULL);
		i++;
	}
}
