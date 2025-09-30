/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkazuhik <mkazuhik@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 03:31:34 by mkazuhik          #+#    #+#             */
/*   Updated: 2025/10/01 04:29:24 by mkazuhik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (validate_and_init(&data, argc, argv) != 0)
		return (1);
	data.start_time = get_time();
	if (create_philosopher_threads(&data) != 0)
		return (1);
	monitor_philosophers(&data);
	wait_for_threads(&data);
	cleanup(&data);
	return (0);
}
