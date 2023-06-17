/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input_check.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: Owen <Owen@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/14 14:39:22 by Owen          #+#    #+#                 */
/*   Updated: 2023/06/17 14:05:27 by ohearn        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*Makes sure all inputs are feasible */
int	value_checker(t_data *data, int ac)
{
	int	i;

	i = 0;
	if (data->philo_nbr < 1)
		i = err(ERR_D_NP);
	if (data->time_to_die == 0)
		i = err(ERR_D_DT);
	if (data->time_to_eat == 0)
		i = err(ERR_D_ET);
	if (data->time_to_sleep == 0)
		i = err(ERR_D_ST);
	if (data->meals_req == 0 && ac == 6)
	{
		i = err(ERR_D_MQ);
		//printf("Simulation has ended.\n");
	}
	return (i);
}

/*Function that makes sure the imput are valid numbers*/
int	input_checker(int ac, char **av)
{
	int		i;
	int		tmp;

	i = 1;
	tmp = 0;
	if (ac != 5 && ac != 6)
	{
		tmp = err(ERR_I_C);
		return (tmp);
	}
	while (av[i])
	{
		if (ft_philoatoi(av[i], 0) < 0)
			return (-2);
		i++;
	}
	return (0);
}
