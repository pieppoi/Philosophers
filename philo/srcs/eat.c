/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    ft +:+         +:+     */
/*   By: mkazuhik <mkazuhik@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 04:36:32 by mkazuhik          #+#    #+#             */
/*   Updated: 2025/10/09 01:39:00 by mkazuhik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	take_forks(t_philo *philo)
{
	if (philo->left_fork < philo->right_fork)
	{
		pthread_mutex_lock(philo->left_mutex);
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(philo->right_mutex);
		print_status(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->right_mutex);
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(philo->left_mutex);
		print_status(philo, "has taken a fork");
	}
}

static void	release_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_mutex);
	pthread_mutex_unlock(philo->right_mutex);
}

static void	update_meal_info(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->meal_mutex);
	philo->state = EATING;
	pthread_mutex_unlock(&philo->data->meal_mutex);
}

void	philosopher_eat(t_philo *philo)
{
	take_forks(philo);
	pthread_mutex_lock(&philo->data->meal_mutex);
	if (!philo->data->all_alive)
	{
		pthread_mutex_unlock(&philo->data->meal_mutex);
		release_forks(philo);
		return ;
	}
	pthread_mutex_unlock(&philo->data->meal_mutex);
	update_meal_info(philo);
	pthread_mutex_lock(&philo->data->meal_mutex);
	philo->last_meal_time = get_time();
	pthread_mutex_unlock(&philo->data->meal_mutex);
	print_status(philo, "is eating");
	precise_usleep(philo->data->time_to_eat * 1000);
	pthread_mutex_lock(&philo->data->meal_mutex);
	philo->meals_eaten++;
	philo->state = SLEEPING;
	pthread_mutex_unlock(&philo->data->meal_mutex);
	release_forks(philo);
}
