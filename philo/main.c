/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: delvira- <delvira-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 11:54:42 by delvira-          #+#    #+#             */
/*   Updated: 2023/03/20 16:42:10 by delvira-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "philo.h"
#include <pthread.h>

void	ft_one_philo(t_data *data)
{
	printf("\n 0 1 has taken a fork");
	ft_sleep(data, data->time_to_die);
	printf("\n %ld 1 died", data->time_to_die);
}

int	main(int nargs, char **args)
{
	t_data	data;

	if (nargs < 5 || nargs > 6)
	{
		printf("Arguments error");
		return (0);
	}
	if (ft_check_data(args) == -1)
	{
		printf("Arguments error (number wrong format)");
		return (0);
	}
	data = init_data(args);
	if (data.n_of_philo == 0)
		return (0);
	ft_init_forks(&data);
	ft_init_philo(&data);
	if (data.n_of_philo == 1)
		ft_one_philo(&data);
	else
		simulation(&data);
	ft_exit(&data);
	return (0);
}
