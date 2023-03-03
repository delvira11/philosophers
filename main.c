/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: delvira- <delvira-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 11:54:42 by delvira-          #+#    #+#             */
/*   Updated: 2023/03/03 20:19:19 by delvira-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "philo.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	sig;
	int	sol;

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

time_t	get_time_in_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

t_data	init_data(char **args)
{
	t_data			data;

	data.n_of_philo = ft_atoi(args[1]);
	data.time_to_die = ft_atoi(args[2]);
	data.time_to_eat = ft_atoi(args[3]);
	data.time_to_sleep = ft_atoi(args[4]);
	if (args[5])
	{
		data.times_must_eat = ft_atoi(args[5]);
	}
	return (data);
}

pthread_mutex_t	*ft_init_forks(t_data *data)
{
	pthread_mutex_t	*forks;
	int				i;

	i = 0;
	forks = malloc(data->n_of_philo * sizeof(pthread_mutex_t));
	//malloc error
	while (i < data->n_of_philo)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&data->write_message, NULL);
	pthread_mutex_init(&data->is_eating, NULL);
	return (forks);
}

t_philo	*ft_init_philo(t_data *data)
{
	t_philo	*philo;
	int		i;

	philo = malloc(data->n_of_philo * sizeof(t_philo));
	//malloc error
	i = 0;
	while (i < data->n_of_philo)
	{
		if (i == (data->n_of_philo - 1))
		{
			philo[i].left_fork = data->forks[i];
			philo[i].right_fork = data->forks[0];
			//printf("\nphilo number %i has fork %i and %i", i + 1, i, 0);
		}
		else
		{
			philo[i].left_fork = data->forks[i];
			philo[i].right_fork = data->forks[i + 1];
			//printf("\nphilo number %i has fork %i and %i", i + 1, i, i + 1);
		}
		philo[i].data = data;
		philo[i].number = i + 1;
		i++;
	}
	return (philo);
}

void	print_message(t_philo *philo, char *message)
{
	t_data *data;

	data = philo->data;

	pthread_mutex_lock(&data->write_message);
	printf("\n%i %s", philo->number, message);
	pthread_mutex_unlock(&data->write_message);
}

void	philo_eat(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	pthread_mutex_lock(&data->write_message);
	pthread_mutex_lock(&philo->left_fork);
	printf("\n %ld %i has taken left fork", (get_time_in_ms() - data->start), philo->number);
	pthread_mutex_unlock(&data->write_message);
	pthread_mutex_lock(&data->write_message);
	pthread_mutex_lock(&philo->right_fork);
	printf("\n %ld %i has taken right fork", (get_time_in_ms() - data->start), philo->number);
	pthread_mutex_unlock(&data->write_message);
	pthread_mutex_lock(&data->write_message);
	pthread_mutex_lock(&data->is_eating);
	printf("\n %ld %i is eating", (get_time_in_ms() - data->start), philo->number);
	pthread_mutex_unlock(&data->is_eating);
	pthread_mutex_unlock(&data->write_message);
	usleep(data->time_to_eat * 1000);
	pthread_mutex_lock(&data->write_message);
	pthread_mutex_unlock(&philo->left_fork);
	pthread_mutex_unlock(&philo->right_fork);
	printf("\n %ld %i stopped eating", (get_time_in_ms() - data->start), philo->number);
	pthread_mutex_unlock(&data->write_message);
}

void	philo_think(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	pthread_mutex_lock(&data->write_message);
	printf("\n %ld %i is thinking", (get_time_in_ms() - data->start), philo->number);
	pthread_mutex_unlock(&data->write_message);
}

void	philo_sleep(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	pthread_mutex_lock(&data->write_message);
	printf("\n %ld %i is sleeping", (get_time_in_ms() - data->start), philo->number);
	pthread_mutex_unlock(&data->write_message);
	usleep(data->time_to_sleep * 1000);
}


void	*philosopher(void *data)
{
	t_philo *philo;
	t_data	*daata;

	int		i;
	philo = (t_philo *) data;
	daata = philo->data;
	i = 1;
	while(i == 1)
	{
		philo_eat(philo);
		philo_think(philo);
		philo_sleep(philo);
	}
	
	return (0);
}

void	simulation(t_data *data)
{
	int	i;
	//int test = 1;

	data->start = get_time_in_ms();
	i = 0;

	while (i < data->n_of_philo)
	{
		pthread_create(&data->philo[i].philo_thread, NULL, philosopher, &data->philo[i]);
		usleep(500000);
		i++;
	}
	sleep(100);
}

int	main(int nargs, char **args)
{
	t_data	data;

	if (nargs < 5 || nargs > 6)
	{
		printf("Arguments error");
		return (0);
	}
	data = init_data(args);
	data.forks = ft_init_forks(&data);
	data.philo = ft_init_philo(&data);
	simulation(&data);
	//printf("\nphil start :%ld", data.philo[4].data->start);	
}
