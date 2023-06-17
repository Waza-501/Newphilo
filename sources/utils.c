/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: Owen <Owen@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/14 16:04:29 by Owen          #+#    #+#                 */
/*   Updated: 2023/06/17 14:21:26 by ohearn        ########   odam.nl         */
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
			i++;
	if (str[i] < '0' || str[i] > '9')
		return (1);
	while (str[i] >= '0' && str[i] <= '9')
		i++;
	if (str[i] != '\0')
		return (-1);
	return (0);
}

/*Atoi modified to work better with philo project.*/
int	ft_philoatoi(const char *str, int tmp)
{
	unsigned long	nbr;
	int		i;

	i = 0;
	nbr = 0;
	if (check_str_atoi(str) != 0)
	{
		tmp = err(ERR_I_N);
		return (tmp);
	}
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
		{
			tmp = err(ERR_I_NN);
			return (tmp);
		}
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		nbr = (nbr * 10) + str[i] - '0';
		i++;
	}
	return (nbr);
}

/*Finds the first node of the list and returns it.*/
t_philo	*search_first(t_philo *list)
{
	while (list && list->prev != NULL)
		list = list->prev;
	return (list);
}
