/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: delvira- <delvira-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 18:39:08 by delvira-          #+#    #+#             */
/*   Updated: 2023/03/17 18:39:44 by delvira-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_data	init_data(char **args)
{
	t_data			data;

	data.n_of_philo = ft_atoi(args[1]);
	data.time_to_die = ft_atoi(args[2]);
	data.time_to_eat = ft_atoi(args[3]);
	data.time_to_sleep = ft_atoi(args[4]);
	data.all_ate = 0;
	data.death_check = 0;
	if (args[5])
	{
		data.times_must_eat = ft_atoi(args[5]);
	}
	else
		data.times_must_eat = -1;
	return (data);
}

void	ft_init_forks(t_data *data)
{
	int				i;

	i = 0;
	data->forks = malloc(data->n_of_philo * sizeof(pthread_mutex_t));
	while (i < data->n_of_philo)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&data->write_message, NULL);
	pthread_mutex_init(&data->eat_lock, NULL);
}

void	ft_init_philo(t_data *data)
{
	int		i;

	data->philo = malloc(data->n_of_philo * sizeof(t_philo));
	i = 0;
	while (i < data->n_of_philo)
	{
		if (i == (data->n_of_philo - 1))
		{
			data->philo[i].left_fork = i;
			data->philo[i].right_fork = 0;
		}
		else
		{
			data->philo[i].left_fork = i;
			data->philo[i].right_fork = i + 1;
		}
		data->philo[i].data = data;
		data->philo[i].number = i + 1;
		data->philo[i].last_time_ate = 0;
		data->philo[i].n_of_meals = 0;
		i++;
	}
}
