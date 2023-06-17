/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   initialize.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: Owen <Owen@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/14 14:40:58 by Owen          #+#    #+#                 */
/*   Updated: 2023/06/17 13:04:49 by ohearn        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	init_mutex(t_data *data, t_philo *philo)
{
	if (pthread_mutex_init(data->print, NULL) != 0)
		return (false);
	if (pthread_mutex_init(data->dead, NULL) != 0)
		return (false);
	while (philo)
	{
		if (pthread_mutex_init(philo->fork, NULL) != 0)
			return (false);
		if (pthread_mutex_init(philo->meal_lock, NULL) != 0)
			return (false);
		philo = philo->next;
	}
	return (true);
}

t_philo	*spawn_philos(t_data *data)
{
	t_philo	*philo;
	t_philo	*temp;
	size_t	count;

	count = 1;
	philo = init_philo(data, count);
	if (!philo)
		return (NULL);
	count++;
	while (count <= data->philo_nbr)
	{
		temp = philo;
		philo->next = init_philo(data, count);
		if (!philo->next)
			return (NULL);
		philo = philo->next;
		philo->prev = temp;
		count++;
	}
	return (search_first(philo));
}

/*Function that fills an emty philo struct with data and
makes sure all memory is correctly allocated*/
t_philo	*init_philo(t_data *data, size_t count)
{
	t_philo	*philo;

	philo = (t_philo *)malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	philo->data = data;
	philo->tag = count;
	philo->finish = false;
	philo->times_eaten = 0;
	philo->last_dinner = 0;
	philo->prev = NULL;
	philo->next = NULL;
	philo->fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	philo->meal_lock = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	if (!philo->fork)
		return (NULL);
	return (philo);
}

/*Function that fills an empty data struct with given input
and makes sure it all gets allocated if needed*/
t_data	*init_data(char **av)
{
	t_data	*data;

	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->philo_nbr = ft_philoatoi(av[1], 0);
	data->time_to_die = ft_philoatoi(av[2], 0);
	data->time_to_eat = ft_philoatoi(av[3], 0);
	data->time_to_sleep = ft_philoatoi(av[4], 0);
	if (av[5])
		data->meals_req = ft_philoatoi(av[5], 0);
	else
		data->meals_req = -1;
	data->starttime = 0;
	data->stop = false;
	data->start = NULL;
	data->print = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	data->dead = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	if (!data->print || !data->dead)
	{
		err(ERR_M);
		return (NULL);
	}
	return (data);
}
