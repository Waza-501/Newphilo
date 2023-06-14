/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   symposium.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: Owen <Owen@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/14 16:39:29 by Owen          #+#    #+#                 */
/*   Updated: 2023/06/14 17:17:11 by Owen          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	end_session(t_data *data, t_philo *philo, pthread_t *threads)
{
	return (true);
}

bool	start_session(t_data *data)
{
	pthread_t	*threads;
	t_philo		*philo;

	threads = create_threads(data);
	philo = spawn_philos(data);
	if (!threads || !philo)
	{
		free_all(data, philo, threads);
		return (false);
	}
	return (true);
}