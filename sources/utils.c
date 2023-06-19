/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: Owen <Owen@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/14 16:04:29 by Owen          #+#    #+#                 */
/*   Updated: 2023/06/19 13:25:48 by Owen          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

static int	check_str_atoi(const char *str)
{
	int		i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			return (err(ERR_I_NN));
		i++;
	}
	if (str[i] < '0' || str[i] > '9')
		return (err(ERR_I_N));
	while (str[i] >= '0' && str[i] <= '9')
		i++;
	if (str[i] != '\0')
		return (err(ERR_I_N));
	return (0);
}

/*Atoi modified to work better with philo project.*/
int	ft_philoatoi(const char *str)
{
	unsigned long	nbr;
	int		i;

	i = 0;
	nbr = 0;
	if (check_str_atoi(str) != 0)
		return (-1);
	while (str[i] >= '0' && str[i] <= '9')
	{
		nbr = (nbr * 10) + str[i] - '0';
		i++;
	}
	if (nbr > INT_MAX)
		return (err(ERR_I_M));
	return (nbr);
}

/*Finds the first node of the list and returns it.*/
t_philo	*search_first(t_philo *list)
{
	while (list && list->prev != NULL)
		list = list->prev;
	return (list);
}
