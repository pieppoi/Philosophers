/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkazuhik <mkazuhik@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 04:24:46 by mkazuhik          #+#    #+#             */
/*   Updated: 2025/10/01 04:55:54 by mkazuhik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	validate_and_init(t_data *data, int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		return (error_exit("Usage: ./philo number_of_philosophers time_to_die "
				"time_to_eat time_to_sleep "
				"[number_of_times_each_philosopher_must_eat]"));
	if (!parse_arguments(argc, argv, data))
		return (error_exit("Failed to parse arguments"));
	if (!init_data(data))
		return (error_exit("Failed to initialize data"));
	if (!init_mutexes(data))
	{
		cleanup(data);
		return (error_exit("Failed to initialize mutexes"));
	}
	if (!init_philos(data))
	{
		cleanup(data);
		return (error_exit("Failed to initialize philosophers"));
	}
	return (0);
}

int	create_philosopher_threads(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->num_philos)
	{
		if (pthread_create(&data->philos[i].thread, NULL, philosopher_routine,
				&data->philos[i]) != 0)
		{
			j = 0;
			while (j < i)
			{
				pthread_join(data->philos[j].thread, NULL);
				j++;
			}
			cleanup(data);
			return (error_exit("Failed to create philosopher thread"));
		}
		i++;
	}
	return (0);
}
