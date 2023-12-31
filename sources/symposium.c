/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   symposium.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: Owen <Owen@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/14 16:39:29 by Owen          #+#    #+#                 */
/*   Updated: 2023/06/20 15:48:22 by ohearn        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*Joins all threads, including grim reaper if
there is more than a singular philosopher*/
bool	end_session(t_data *data, pthread_t *threads)
{
	join_threads(threads, data->philo_nbr);
	if (data->philo_nbr > 1)
		pthread_join(data->grim_reaper, NULL);
	return (true);
}

/*Runs this if there is just one philo*/
static void	*single_philo(t_data *data, t_philo *philo)
{
	pthread_mutex_lock(philo->fork);
	print_status(philo, false, FORK);
	c_sleep(data, data->time_to_die);
	print_status(philo, false, DEATH);
	pthread_mutex_unlock(philo->fork);
	return (NULL);
}

/*Philosopher thread routine. Staggers even numbered
philosophers so the process runs smoothly.*/
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

/*Starts thread creation and sets a delay so the simulation
starts when all threads are there, including the grim_reaper*/
int	start_sim(t_data *data, t_philo *philo, pthread_t *threads)
{
	size_t	i;

	i = 0;
	if (init_mutex(data) != true)
		return (false);
	data->starttime = get_current_time() + (data->philo_nbr * 2 * 10);
	while (i < data->philo_nbr)
	{
		if (pthread_create(&threads[i], NULL, &philosopher,
				(void *)philo) != 0)
			return (thread_error(data, threads, i));
		philo = philo->next;
		i++;
	}
	if (data->philo_nbr > 1)
	{
		if (pthread_create(&data->grim_reaper, NULL,
				&grim_reaper, (void *)data) != 0)
			return (-2);
	}
	return (0);
}

/*Prepares everything and makes sure it's all there
before starting the simulation. Will make sure
all allocated memory is freed if an error occurs
or if the simulation ends through meals_req*/
bool	start_session(t_data *data)
{
	pthread_t	*threads;
	t_philo		*philo;

	threads = create_threads(data);
	philo = spawn_philos(data);
	if (!threads || !philo)
	{
		err(ERR_TP);
		free_all(data, philo, threads);
		return (false);
	}
	data->start = philo;
	if (start_sim(data, philo, threads) < 0)
	{
		if (check_status(data) == true)
			return (free_all(data, philo, threads));
		err(ERR_T_F);
		set_finish(data, true);
		end_session(data, threads);
		return (free_all(data, philo, threads));
	}
	if (end_session(data, threads) == false)
		return (free_all(data, philo, threads));
	free_all(data, philo, threads);
	return (true);
}
