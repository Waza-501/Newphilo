/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   threads.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: Owen <Owen@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/14 23:08:33 by Owen          #+#    #+#                 */
/*   Updated: 2023/06/20 15:40:18 by ohearn        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*Joins all threads*/
pthread_t	join_threads(pthread_t *threads, size_t amount)
{
	size_t	collected;

	collected = 0;
	while (collected < amount)
	{
		pthread_join(threads[collected], NULL);
		collected++;
	}
	return (NULL);
}

/*Allocates the memory needed for all the threads*/
pthread_t	*create_threads(t_data *data)
{
	pthread_t	*threads;

	threads = (pthread_t *)malloc(sizeof(pthread_t) * data->philo_nbr);
	return (threads);
}
