/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: delvira- <delvira-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 18:37:22 by delvira-          #+#    #+#             */
/*   Updated: 2023/03/17 18:38:45 by delvira-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_atoi(const char *str)
{
	int		i;
	int		sig;
	long	sol;

	i = 0;
	sig = 1;
	sol = 0;
	while ((str[i] >= '\t' && str[i] <= '\r') || (str[i] == ' '))
		i++;
	if ((str[i] == '-') || (str[i] == '+'))
	{
		if (str[i] == '-')
		{
			sig *= -1;
		}
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		sol *= 10;
		sol += str[i] - '0';
		i++;
	}
	return (sol * sig);
}

int	ft_parse_num(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] > '9' || str[i] < '0')
			return (1);
		i++;
	}
	if (ft_atoi(str) > 2147483647 || ft_atoi(str) < -2147483648)
		return (1);
	return (0);
}

int	ft_check_data(char **args)
{
	if (ft_parse_num(args[1]) == 1)
		return (-1);
	if (ft_parse_num(args[2]) == 1)
		return (-1);
	if (ft_parse_num(args[3]) == 1)
		return (-1);
	if (ft_parse_num(args[4]) == 1)
		return (-1);
	if (args[5])
	{
		if (ft_parse_num(args[5]) == 1)
			return (-1);
	}
	return (0);
}

void	print_message(t_philo *philo, char *message)
{
	t_data	*data;

	data = philo->data;
	pthread_mutex_lock(&data->write_message);
	if (data->death_check != 1 && data->all_ate != 1)
	{
		printf("\n %ld %i %s", (get_time_in_ms()
				- data->start), philo->number, message);
	}
	pthread_mutex_unlock(&data->write_message);
	return ;
}
