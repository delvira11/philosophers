/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: delvira- <delvira-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 18:40:16 by delvira-          #+#    #+#             */
/*   Updated: 2023/06/19 16:46:10 by delvira-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philosopher(void *data)
{
	t_philo	*philo;
	t_data	*daata;

	philo = (t_philo *) data;
	daata = philo->data;
	while (philo->data->death_check != 1 && philo->data->all_ate != 1)
	{
		if ((philo->number % 2) == 0)
			philo_eat_left(philo);
		else
			philo_eat_right(philo);
		philo_sleep(philo);
		philo_think(philo);
	}
	return (0);
}

void	line_redu(t_data *data, t_philo *philo, int i)
{
	pthread_mutex_lock(&data->write_message);
	printf("\n %ld %i died", (get_time_in_ms()
			- data->start), philo[i].number);
	pthread_mutex_unlock(&data->write_message);
	data->death_check = 1;
	pthread_mutex_unlock(&data->eat_lock);
}

void	death_checker(t_philo *philo)
{
	t_data	*data;
	int		i;

	data = philo->data;
	while (data->all_ate != 1)
	{
		i = -1;
		while (++i < data->n_of_philo && data->death_check != 1)
		{
			pthread_mutex_lock(&data->eat_lock);
			if ((get_time_in_ms() - philo[i].last_time_ate) > data->time_to_die)
			{
				line_redu(data, philo, i);
				return ;
			}
			pthread_mutex_unlock(&data->eat_lock);
			usleep(100);
		}
		i = 0;
		while (data->times_must_eat != -1 && i < data->n_of_philo
			&& philo[i].n_of_meals >= data->times_must_eat)
			i++;
		if (i == data->n_of_philo)
			data->all_ate = 1;
	}
}

void	ft_exit(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_of_philo)
	{
		pthread_join(data->philo[i].philo_thread, NULL);
		i++;
	}
	i = 0;
	while (i < data->n_of_philo)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data->eat_lock);
	pthread_mutex_destroy(&data->write_message);
	return ;
}

void	simulation(t_data *data)
{
	int	i;

	data->start = get_time_in_ms();
	i = 0;
	while (i < data->n_of_philo)
	{
		data->philo[i].last_time_ate = data->start;
		pthread_create(&data->philo[i].philo_thread, NULL, philosopher, &data->philo[i]);
		i++;
	}
	death_checker(data->philo);
}
