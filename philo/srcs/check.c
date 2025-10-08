/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkazuhik <mkazuhik@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 05:25:22 by mkazuhik          #+#    #+#             */
/*   Updated: 2025/10/09 01:37:59 by mkazuhik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_philosopher_status(t_philo *philo)
{
	int	status;

	pthread_mutex_lock(&philo->data->meal_mutex);
	status = philo->data->all_alive && !philo->data->all_fed;
	pthread_mutex_unlock(&philo->data->meal_mutex);
	return (status);
}

int	check_all_fed(t_data *data)
{
	int	i;

	if (data->num_meals <= 0)
		return (0);
	pthread_mutex_lock(&data->meal_mutex);
	i = 0;
	while (i < data->num_philos)
	{
		if (data->philos[i].meals_eaten < data->num_meals)
		{
			pthread_mutex_unlock(&data->meal_mutex);
			return (0);
		}
		i++;
	}
	data->all_fed = 1;
	pthread_mutex_unlock(&data->meal_mutex);
	return (1);
}
