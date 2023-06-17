/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cleanup.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: Owen <Owen@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/14 16:42:45 by Owen          #+#    #+#                 */
/*   Updated: 2023/06/17 14:50:25 by Owen          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*Free everything in the data struct*/
static void	free_data(t_data *data)
{
	if (data->print)
	{
		pthread_mutex_destroy(data->print);
		free(data->print);
	}
	if (data->dead)
	{
		pthread_mutex_destroy(data->dead);
		free(data->dead);
	}
	free (data);
}

/*Free everything in the philo struct*/
static void	free_philo(t_philo *philo)
{
	t_philo	*temp;

	while (philo)
	{
		temp = philo->next;
		if (philo->fork)
		{
			pthread_mutex_destroy(philo->fork);
			free(philo->fork);
		}
		if (philo->meal_lock)
		{
			pthread_mutex_destroy(philo->meal_lock);
			free(philo->meal_lock);
		}
		free(philo);
		philo = temp;
	}
}

/*If present, will free the given structs/allocated memory*/
void	free_all(t_data *data, t_philo *philo, pthread_t *threads)
{
	if (data)
		free_data(data);
	if (philo)
		free_philo(philo);
	free(threads);
}
