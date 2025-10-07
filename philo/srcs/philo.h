/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkazuhik <mkazuhik@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 03:31:55 by mkazuhik          #+#    #+#             */
/*   Updated: 2025/10/01 04:49:19 by mkazuhik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <pthread.h>
# include <sys/time.h>

# define MAX_PHILOS 200

typedef enum e_state
{
	THINKING,
	EATING,
	SLEEPING,
	DEAD
}	t_state;

typedef struct s_philo
{
	int				id;
	int				left_fork;
	int				right_fork;
	long			last_meal_time;
	int				meals_eaten;
	t_state			state;
	pthread_t		thread;
	pthread_mutex_t	*left_mutex;
	pthread_mutex_t	*right_mutex;
	struct s_data	*data;
}	t_philo;

typedef struct s_data
{
	int				num_philos;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				num_meals;
	long			start_time;
	int				all_alive;
	int				all_fed;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
    pthread_mutex_t	meal_mutex;
    pthread_mutex_t	start_mutex;
    pthread_cond_t	start_cond;
    int				started;
	t_philo			*philos;
}	t_data;

// Main functions
int		main(int argc, char **argv);
int		parse_arguments(int argc, char **argv, t_data *data);
int		init_data(t_data *data);
int		init_philos(t_data *data);
int		init_mutexes(t_data *data);
void	cleanup(t_data *data);

// Main utility functions
int		validate_and_init(t_data *data, int argc, char **argv);
int		create_philosopher_threads(t_data *data);
void	start_simulation(t_data *data);

// Monitor functions
void	monitor_philosophers(t_data *data);
void	wait_for_threads(t_data *data);

// Parse utility functions
void	cleanup_forks(t_data *data, int count);
int		init_fork_mutexes(t_data *data);
int		init_other_mutexes(t_data *data);

// Philosopher functions
void	*philosopher_routine(void *arg);
void	philosopher_eat(t_philo *philo);

// Utility functions
long	get_time(void);
void	precise_usleep(long microseconds);
void	print_status(t_philo *philo, const char *status);
int		check_death(t_philo *philo);
int		check_all_fed(t_data *data);

// Error handling
int		error_exit(const char *message);

#endif
