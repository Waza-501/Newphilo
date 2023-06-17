/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   grim_reaper.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: Owen <Owen@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/16 09:45:29 by Owen          #+#    #+#                 */
/*   Updated: 2023/06/17 17:59:49 by ohearn        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_finish(t_data *data, int status)
{
	pthread_mutex_lock(data->dead);
	data->stop = status;
	pthread_mutex_unlock(data->dead);
}

bool	check_status(t_data *data)
{
	bool	status;

	status = false;
	pthread_mutex_lock(data->dead);
	if (data->stop == true)
		status = true;
	pthread_mutex_unlock(data->dead);
	return (status);
}

bool	kill_philo(t_data *data, t_philo *philo)
{
	time_t	time;

	time = get_current_time();
	if ((time - philo->last_dinner) >= data->time_to_die)
	{
		set_finish(data, true);
		print_status(philo, true, DEATH);
		pthread_mutex_unlock(philo->meal_lock);
		return (true);
	}
	return (false);
}

bool	is_finished(t_data *data)
{
	t_philo		*philo;
	bool		satiated;

	philo = data->start;
	satiated = true;
	philo = data->start;
	while (philo)
	{
		pthread_mutex_lock(philo->meal_lock);
		if (kill_philo(data, philo) == true)
			return (true);
		if (data->meals_req != -1)
			if (philo->times_eaten < (unsigned int) data->meals_req)
				satiated = false;
		pthread_mutex_unlock(philo->meal_lock);
		philo = philo->next;
	}
	if (data->meals_req != -1 && satiated == true)
	{
		set_finish(data, true);
		return (true);
	}
	return (false);
}

/*thread routine that will check if a philosopher needs
to be killed, doing so every x microseconds*/
void	*grim_reaper(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	if (data->meals_req == 0)
		return (NULL);
	set_finish(data, false);
	delay_start(data);
	while (true)
	{
		if (is_finished(data) == true)
			return (NULL);
		usleep(1000);
	}
	return (NULL);
}
