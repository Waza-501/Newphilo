/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   symposium.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: Owen <Owen@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/14 16:39:29 by Owen          #+#    #+#                 */
/*   Updated: 2023/06/17 14:27:43 by ohearn        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	end_session(t_data *data, t_philo *philo, pthread_t *threads)
{
	join_threads(threads, data->philo_nbr);
	if (data->philo_nbr > 1)
		pthread_join(data->grim_reaper, NULL);
	free_all(data, philo, threads);
	return (true);
}

/*Run this if there is just one philo*/
static void	*single_philo(t_data *data, t_philo *philo)
{
	pthread_mutex_lock(philo->fork);
	print_status(philo, false, FORK);
	c_sleep(data, data->time_to_die);
	print_status(philo, false, DEATH);
	pthread_mutex_unlock(philo->fork);
	return (NULL);
}

void	*philosopher(void *input)
{
	t_philo	*philo;

	philo = (t_philo *)input;
	if (philo->data->meals_req == 0)
		return (NULL);
	pthread_mutex_lock(philo->meal_lock);
	philo->last_dinner = philo->data->starttime;
	pthread_mutex_unlock(philo->meal_lock);
	delay_start(philo->data);
	if (philo->data->time_to_die == 0)
		return (NULL);
	if (philo->data->philo_nbr == 1)
		return (single_philo(philo->data, philo));
	else if (philo->tag % 2)
		think_time(philo->data, philo, true);
	while (check_status(philo->data) == false)
	{
		eat_sleep(philo->data, philo);
		think_time(philo->data, philo, false);
	}
	return (NULL);
}

bool	start_sim(t_data *data, t_philo *philo, pthread_t *threads)
{
	size_t	i;

	i = 0;
	if (init_mutex(data, philo) != true)
		return (false);
	data->starttime = get_current_time() + (data->philo_nbr * 2 * 10);
	while (i < data->philo_nbr)
	{
		if (pthread_create(&threads[i], NULL, &philosopher,
				(void *)philo) != 0)
			return (false);
		philo = philo->next;
		i++;
	}
	if (data->philo_nbr > 1)
	{
		if (pthread_create(&data->grim_reaper, NULL,
				&grim_reaper, (void *)data) != 0)
			return (false);
	}
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
	data->start = philo;
	if (start_sim(data, philo, threads) == false)
	{
		err(ERR_FND);
		set_finish(data, true);
		free_all(data, philo, threads);
		return (false);
	}
	if (end_session(data, philo, threads) == false)
		return (err(ERR_FND));
	return (true);
}
