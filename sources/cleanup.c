/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cleanup.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: Owen <Owen@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/14 16:42:45 by Owen          #+#    #+#                 */
/*   Updated: 2023/06/14 17:10:38 by Owen          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*Free everything in the data struct*/
static void	free_data(t_data *data)
{
	if (data->meal_lock)
	{
		pthread_mutex_destroy(data->meal_lock);
		free(data->meal_lock);
	}
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
	printf("Data is free\n");
	free (data);
}

/*Free everything in the philo struct*/
static void	free_philo(t_philo *philo)
{
	t_philo	*temp;

	while (philo)
	{
		temp = philo->next;
		if (!philo->fork)
		{
			pthread_mutex_destroy(philo->fork);
			free(philo->fork);
		}
		free(philo);
		philo = temp;
	}
	printf("All philosophers are free\n");
}

/*If present, will free the given structs/allocated memory*/
void	free_all(t_data *data, t_philo *philo, pthread_t *threads)
{
	if (data)
		free_data(data);
	if (philo)
		free_philo(philo);
	free(threads);
	sleep(1);
	printf("All information is gone :D\n");
}