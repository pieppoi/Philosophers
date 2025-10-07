/* ************************************************************************** */
/*	*/
/*	:::	  ::::::::   */
/*   philosopher.c	  ::	  ::	::   */
/*	: :	 :	 */
/*   By: mkazuhik <mkazuhik@student.42tokyo.jp>	 #  :	   #	*/
/*	#####   #	   */
/*   Created: 2025/10/01 03:32:02 by mkazuhik	  ##	##	 */
/*   Updated: 2025/10/06 19:21:25 by mkazuhik	 ###   ########.fr	   */
/*	*/
/* ************************************************************************** */

#include "philo.h"

static void	stagger_start(t_philo *philo)
{
	int	is_odd_count;

	is_odd_count = (philo->data->num_philos % 2) != 0;
	if (is_odd_count)
	{
		if ((philo->id % 2) == 0)
			precise_usleep(philo->data->time_to_eat * 1000);
	}
	else
	{
		if ((philo->id % 2) == 0)
			precise_usleep((philo->data->time_to_eat * 1000) / 2);
	}
}

static int	check_philosopher_status(t_philo *philo)
{
	int	status;

	pthread_mutex_lock(&philo->data->meal_mutex);
	status = philo->data->all_alive && !philo->data->all_fed;
	pthread_mutex_unlock(&philo->data->meal_mutex);
	return (status);
}

static void	handle_single_philosopher(t_philo *philo)
{
	pthread_mutex_lock(philo->left_mutex);
	print_status(philo, "has taken a fork");
	precise_usleep(philo->data->time_to_die * 1000);
	pthread_mutex_unlock(philo->left_mutex);
}

static void	philosopher_cycle(t_philo *philo)
{
	while (check_philosopher_status(philo))
	{
		philosopher_eat(philo);
		if (!check_philosopher_status(philo))
			break ;
		philo->state = SLEEPING;
		print_status(philo, "is sleeping");
		precise_usleep(philo->data->time_to_sleep * 1000);
		if (!check_philosopher_status(philo))
			break ;
		philo->state = THINKING;
		print_status(philo, "is thinking");
		if ((philo->data->num_philos % 2) != 0)
			precise_usleep(philo->data->time_to_eat * 1000);
	}
}

void	*philosopher_routine(void *arg)
{
	t_philo	*philo;

    philo = (t_philo *)arg;
    pthread_mutex_lock(&philo->data->start_mutex);
    while (!philo->data->started)
        pthread_cond_wait(&philo->data->start_cond, &philo->data->start_mutex);
    pthread_mutex_unlock(&philo->data->start_mutex);
	stagger_start(philo);
	if (philo->data->num_philos == 1)
	{
		handle_single_philosopher(philo);
		return (NULL);
	}
	philosopher_cycle(philo);
	return (NULL);
}
