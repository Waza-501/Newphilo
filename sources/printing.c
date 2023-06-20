/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   printing.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: Owen <Owen@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/14 16:24:37 by Owen          #+#    #+#                 */
/*   Updated: 2023/06/20 15:25:37 by ohearn        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*Prints the requested error message to STDERR.*/
int	err(char *str)
{
	write (STDERR_FILENO, "Error: ", 8);
	write (STDERR_FILENO, str, ft_strlen(str));
	write (STDERR_FILENO, "\n", 1);
	return (-1);
}

/*Prints the message*/
static void	sim_print(t_philo *philo, char *str)
{
	bool	debug;

	debug = false;
	if (debug == false)
		printf("%ld %zu %s\n", get_current_time()
			- philo->data->starttime, philo->tag, str);
}

/*Based on the given inputs, prints the message
associated with it. In case the simulation has ended
and it's not the death message print, it does nothing*/
void	print_status(t_philo *philo, bool death, t_status status)
{
	pthread_mutex_lock(philo->data->print);
	if (check_status(philo->data) == true && death == false)
	{
		pthread_mutex_unlock(philo->data->print);
		return ;
	}
	if (status == FORK)
		sim_print(philo, "has taken a fork");
	else if (status == EAT)
		sim_print(philo, "is eating");
	else if (status == THINK)
		sim_print(philo, "is thinking");
	else if (status == SLEEP)
		sim_print(philo, "is sleeping");
	else if (status == DEATH)
		sim_print(philo, "died");
	else if (status == FINISHED)
		printf("%s\n", FIN);
	pthread_mutex_unlock(philo->data->print);
}
