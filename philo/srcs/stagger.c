/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stagger.c                                          :+:      :+:    :+:   */
/*                                                    ft +:+         +:+     */
/*   By: mkazuhik <mkazuhik@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 03:32:02 by mkazuhik          #+#    #+#             */
/*   Updated: 2025/10/09 01:39:00 by mkazuhik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	stagger_large_group(t_philo *philo)
{
	if (philo->id % 4 == 1)
		precise_usleep(0);
	else if (philo->id % 4 == 2)
		precise_usleep(50000);
	else if (philo->id % 4 == 3)
		precise_usleep(100000);
	else
		precise_usleep(150000);
}

static void	stagger_small_group(t_philo *philo)
{
	int		is_odd_count;
	long	stagger_delay;

	if (philo->data->num_philos > 50)
	{
		stagger_delay = (philo->id * 200) % (philo->data->time_to_eat * 1000);
		precise_usleep(stagger_delay);
	}
	else
	{
		is_odd_count = (philo->data->num_philos % 2) != 0;
		if (is_odd_count)
		{
			if ((philo->id % 2) == 0)
				precise_usleep(1000);
		}
		else
		{
			if ((philo->id % 2) == 0)
				precise_usleep(1000);
		}
	}
}

void	stagger_start(t_philo *philo)
{
	if (philo->data->num_philos > 100)
		stagger_large_group(philo);
	else if (philo->data->num_philos > 50)
		stagger_small_group(philo);
	else
		stagger_small_group(philo);
}
