/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   initialize.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: Owen <Owen@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/14 14:40:58 by Owen          #+#    #+#                 */
/*   Updated: 2023/06/14 16:38:43 by Owen          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_data	*init_data(char **av)
{
	t_data *data;

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
	data->finish = false;
	data->meal_lock = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	data->print = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	data->dead = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	if (!data->meal_lock || !data->print || !data->dead)
	{
		err(ERR_M);
		return (NULL);
	}
	return (data);	
}
