/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: delvira- <delvira-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 18:35:36 by delvira-          #+#    #+#             */
/*   Updated: 2023/03/17 18:35:55 by delvira-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_eat_left(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	pthread_mutex_lock(&(data->forks[philo->left_fork]));
	print_message(philo, "has taken a fork");
	pthread_mutex_lock(&(data->forks[philo->right_fork]));
	print_message(philo, "has taken a fork");
	pthread_mutex_lock(&data->eat_lock);
	print_message(philo, "is eating");
	philo->last_time_ate = get_time_in_ms();
	pthread_mutex_unlock(&data->eat_lock);
	ft_sleep(data, data->time_to_eat);
	philo->n_of_meals += 1;
	pthread_mutex_unlock(&(data->forks[philo->left_fork]));
	pthread_mutex_unlock(&(data->forks[philo->right_fork]));
}

void	philo_eat_right(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	pthread_mutex_lock(&(data->forks[philo->right_fork]));
	print_message(philo, "has taken a fork");
	pthread_mutex_lock(&(data->forks[philo->left_fork]));
	print_message(philo, "has taken a fork");
	pthread_mutex_lock(&data->eat_lock);
	print_message(philo, "is eating");
	philo->last_time_ate = get_time_in_ms();
	pthread_mutex_unlock(&data->eat_lock);
	ft_sleep(data, data->time_to_eat);
	philo->n_of_meals += 1;
	pthread_mutex_unlock(&(data->forks[philo->right_fork]));
	pthread_mutex_unlock(&(data->forks[philo->left_fork]));
}

void	philo_think(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	print_message(philo, "is thinking");
}

void	philo_sleep(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	print_message(philo, "is sleeping");
	ft_sleep(data, data->time_to_sleep);
}
