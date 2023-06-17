/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: Owen <Owen@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/14 14:36:35 by Owen          #+#    #+#                 */
/*   Updated: 2023/06/17 13:10:53 by ohearn        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// static void	checkleaks(void)
// {
// 	system("leaks -q philo");
// }

int	main(int ac, char **av)
{
	t_data	*data;

	//atexit(checkleaks);
	if (input_checker(ac, av) != 0)
		return (-1);
	data = init_data(av);
	if (!data)
	{
		free_all(data, NULL, NULL);
		return (-1);
	}
	if (value_checker(data, ac) != 0)
	{
		free_all(data, NULL, NULL);
		return (-1);
	}
	if (start_session(data) == false)
		return (err(ERR_FND));
	printf("Simulation has ended\n");
	return (0);
}
