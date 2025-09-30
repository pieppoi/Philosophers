/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkazuhik <mkazuhik@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 04:24:46 by mkazuhik          #+#    #+#             */
/*   Updated: 2025/10/01 04:54:16 by mkazuhik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	validate_input(int argc, char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (i < argc)
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

static int	parse_values(int argc, char **argv, t_data *data)
{
	data->num_philos = atoi(argv[1]);
	data->time_to_die = atoi(argv[2]);
	data->time_to_eat = atoi(argv[3]);
	data->time_to_sleep = atoi(argv[4]);
	data->num_meals = -1;
	if (argc == 6)
		data->num_meals = atoi(argv[5]);
	return (1);
}

static int	validate_values(t_data *data, int argc)
{
	if (data->num_philos <= 0 || data->num_philos > MAX_PHILOS)
		return (0);
	if (data->time_to_die <= 0 || data->time_to_eat <= 0
		|| data->time_to_sleep <= 0)
		return (0);
	if (argc == 6 && data->num_meals <= 0)
		return (0);
	return (1);
}

int	parse_arguments(int argc, char **argv, t_data *data)
{
	if (!validate_input(argc, argv))
		return (0);
	if (!parse_values(argc, argv, data))
		return (0);
	if (!validate_values(data, argc))
		return (0);
	return (1);
}
