/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: Owen <Owen@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/14 14:36:35 by Owen          #+#    #+#                 */
/*   Updated: 2023/06/20 15:45:37 by ohearn        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_data	*data;

	if (input_checker(ac, av) != 0)
		return (-1);
	data = init_data(av);
	if (!data)
	{
		err(ERR_M);
		free_all(data, NULL, NULL);
		return (-1);
	}
	if (value_checker(data, ac) != 0)
	{
		free_all(data, NULL, NULL);
		return (-1);
	}
	if (start_session(data) == false)
		return (-1);
	return (0);
}
