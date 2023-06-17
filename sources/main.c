/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: Owen <Owen@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/14 14:36:35 by Owen          #+#    #+#                 */
/*   Updated: 2023/06/17 08:32:19 by Owen          ########   odam.nl         */
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
		//printf("It fails at step 1 bruh\n");
		free_all(data, NULL, NULL);
		return (-1);
	}
	if (value_checker(data, ac) != 0)
	{
		//printf("It fails at step 2 bruh\n");
		free_all(data, NULL, NULL);
		return (-1);
	}
	if (start_session(data) == false)
		return (err(ERR_FND));
	printf("Simulation has ended\n");
	return (0);
}
