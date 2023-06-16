/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   eat_sleep_think.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: Owen <Owen@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/16 10:40:05 by Owen          #+#    #+#                 */
/*   Updated: 2023/06/16 18:59:43 by Owen          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*Unlocks the forks that the philosopher used*/
void	drop_forks(t_philo *philo)
{
	t_philo	*temp;

	temp = search_first(philo);
	pthread_mutex_unlock(philo->fork);
	if (philo->next)
		pthread_mutex_unlock(philo->next->fork);
	else
		pthread_mutex_unlock(temp->fork);
	//printf("forks dropped for philo %zu\n", philo->tag);
}

/*Locks the forks that the philosopher will use*/
static void	grab_forks(t_philo *philo)
{
	t_philo	*temp;

	temp = search_first(philo);
	pthread_mutex_lock(philo->fork);
	print_status(philo, false, FORK);
	if (philo->next)
		pthread_mutex_lock(philo->next->fork);
	else
		pthread_mutex_lock(temp->fork);
	print_status(philo, false, FORK);
}

/*Custom think function based on different (time) inputs*/
void	think_time(t_data *data, t_philo *philo, bool start)
{
	time_t	think_timer;

	pthread_mutex_lock(philo->meal_lock);
	//printf("philo tag is %zu\n", philo->tag);
	think_timer = (data->time_to_die
			- (get_current_time() - philo->last_dinner)
			- data->time_to_eat) / 2;
	//printf("timer is %li\n", think_timer);
	pthread_mutex_unlock(philo->meal_lock);
	if (think_timer < 0)
		think_timer = 0;
	if (think_timer == 0 && start == true)
	{
		//printf("waiting so forks aren't mega yoinked\n");
		think_timer = 1;
	}
	if (think_timer > 500)
		think_timer = 200;
	if (start == false)
		print_status(philo, false, THINK);
	c_sleep(data, think_timer);
}

/*Eat and sleep nicely fitted into one function.*/
void	eat_sleep(t_data *data, t_philo *philo)
{
	//printf("entering eat and sleep routine\n");
	grab_forks(philo);
	print_status(philo, false, EAT);
	pthread_mutex_lock(philo->meal_lock);
	//printf("dinnertime updated for philo %zu\n", philo->tag);
	philo->last_dinner = get_current_time();
	pthread_mutex_unlock(philo->meal_lock);
	c_sleep(data, data->time_to_eat);
	drop_forks(philo);
	if (check_status(data) == false)
	{
		pthread_mutex_lock(philo->meal_lock);
		philo->times_eaten++;
		pthread_mutex_unlock(philo->meal_lock);
	}
	print_status(philo, false,  SLEEP);
	c_sleep(data, data->time_to_sleep);
}