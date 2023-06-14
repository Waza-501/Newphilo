/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   printing.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: Owen <Owen@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/14 16:24:37 by Owen          #+#    #+#                 */
/*   Updated: 2023/06/14 17:05:39 by Owen          ########   odam.nl         */
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

// void	zero_meals(void)
// {
// 	printf("Simulation has ended.\n");
// }

static void	sim_print(t_data *data, t_philo *philo, char *str)
{
	bool	debug;

	debug = false;
	if (data->finish == false && debug == false)
		printf("%ld %zu %s\n", get_current_time()
			- data->starttime, philo->tag, str);
}

void	print_status(t_data *data, t_philo *philo, t_status status)
{
	pthread_mutex_lock(data->dead);
	pthread_mutex_lock(data->print);
	if (status == FORK)
		sim_print(data, philo, "has taken a fork");
	else if (status == EAT)
		sim_print(data, philo, "is eating");
	else if (status == THINK)
		sim_print(data, philo, "is thinking");
	else if (status == SLEEP)
		sim_print(data, philo, "is sleeping");
	else if (status == DEATH)
		printf("%ld %zu has died\n",
			get_current_time() - data->starttime, philo->tag);
	else if (status == FINISHED)
		printf("%s\n", FIN);
	pthread_mutex_unlock(data->dead);
	pthread_mutex_unlock(data->print);
}
