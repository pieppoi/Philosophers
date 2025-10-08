/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    ft +:+         +:+     */
/*   By: mkazuhik <mkazuhik@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 03:32:02 by mkazuhik          #+#    #+#             */
/*   Updated: 2025/10/09 01:39:00 by mkazuhik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	handle_single_philosopher(t_philo *philo)
{
	pthread_mutex_lock(philo->left_mutex);
	print_status(philo, "has taken a fork");
	precise_usleep(philo->data->time_to_die * 1000);
	pthread_mutex_unlock(philo->left_mutex);
}

void	philosopher_sleep(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->meal_mutex);
	philo->state = SLEEPING;
	pthread_mutex_unlock(&philo->data->meal_mutex);
	print_status(philo, "is sleeping");
	precise_usleep(philo->data->time_to_sleep * 1000);
}

void	philosopher_think(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->meal_mutex);
	philo->state = THINKING;
	pthread_mutex_unlock(&philo->data->meal_mutex);
	print_status(philo, "is thinking");
	if (philo->data->num_philos > 100)
		precise_usleep((philo->id % 10) * 1000);
	else if ((philo->data->num_philos % 2) != 0)
		precise_usleep(philo->data->time_to_eat * 1000);
}

void	philosopher_cycle(t_philo *philo)
{
	while (check_philosopher_status(philo))
	{
		philosopher_eat(philo);
		if (!check_philosopher_status(philo))
			break ;
		philosopher_sleep(philo);
		if (!check_philosopher_status(philo))
			break ;
		philosopher_think(philo);
	}
}

void	*philosopher_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->data->num_philos == 1)
	{
		handle_single_philosopher(philo);
		return (NULL);
	}
	stagger_start(philo);
	philosopher_cycle(philo);
	return (NULL);
}
