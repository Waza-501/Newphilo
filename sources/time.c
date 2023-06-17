/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   time.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: Owen <Owen@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/14 16:59:53 by Owen          #+#    #+#                 */
/*   Updated: 2023/06/17 18:01:16 by ohearn        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*Function that grabs the current time in ms*/
time_t	get_current_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	delay_start(t_data *data)
{
	while (get_current_time() < data->starttime && check_status(data) == false)
		continue ;
}

/*Custom sleep function that sleeps in 100 microsecond
intervals, stopping early if the simulation has ended*/
void	c_sleep(t_data *data, size_t sleeptime)
{
	time_t	timer;

	timer = get_current_time() + sleeptime;
	while (get_current_time() < timer)
	{
		if (check_status(data) == true)
			break ;
		usleep(200);
	}
}
