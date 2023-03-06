/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: delvira- <delvira-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 11:54:42 by delvira-          #+#    #+#             */
/*   Updated: 2023/03/06 17:19:35 by delvira-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "philo.h"
#include <pthread.h>


time_t	ft_now(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

time_t	ft_time_diff(time_t past, time_t pre)
{
	return (pre - past);
}

void	ft_sleep(t_data *data, time_t sleep)
{
	time_t	wake_up;

	wake_up = ft_now();
	while (!(data->death_check))
	{
		if (ft_time_diff(wake_up, ft_now()) >= sleep)
			break ;
	}
}



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
	data.death_check = 0;
	if (args[5])
	{
		data.times_must_eat = ft_atoi(args[5]);
	}
	return (data);
}

void	ft_init_forks(t_data *data)
{
	int				i;

	i = 0;
	data->forks = malloc(data->n_of_philo * sizeof(pthread_mutex_t));
	//malloc error
	while (i < data->n_of_philo)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&data->write_message, NULL);
	pthread_mutex_init(&data->meal_check, NULL);
}

void    ft_init_philo(t_data *data)
{
	int		i;

	data->philo = malloc(data->n_of_philo * sizeof(t_philo));
	//malloc error
	i = 0;
	while (i < data->n_of_philo)
	{
		if (i == (data->n_of_philo - 1))
		{
			data->philo[i].left_fork = i;
			data->philo[i].right_fork = 0;
			//printf("\nphilo number %i has fork %i and %i", i + 1, i, 0);
		}
		else
		{
			data->philo[i].left_fork = i;
			data->philo[i].right_fork = i + 1;
			//printf("\nphilo number %i has fork %i and %i", i + 1, i, i + 1);
		}
		data->philo[i].data = data;
		data->philo[i].number = i + 1;
		data->philo[i].last_time_ate = 0;
		pthread_mutex_init(&data->philo[i].eat_lock, NULL);
		pthread_mutex_init(&data->philo[i].death_lock, NULL);
		i++;
	}
}

void	print_message(t_philo *philo, char *message)
{
	t_data *data;

	data = philo->data;

	pthread_mutex_lock(&data->write_message);
	printf("\n%i %s", philo->number, message);
	pthread_mutex_unlock(&data->write_message);
}

void	philo_eat_left(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	pthread_mutex_lock(&(data->forks[philo->left_fork]));
	pthread_mutex_lock(&data->write_message);
	printf("\n %ld %i has taken left fork", (get_time_in_ms() - data->start), philo->number);
	pthread_mutex_unlock(&data->write_message);
	pthread_mutex_lock(&(data->forks[philo->right_fork]));
	pthread_mutex_lock(&data->write_message);
	printf("\n %ld %i has taken right fork", (get_time_in_ms() - data->start), philo->number);
	pthread_mutex_unlock(&data->write_message);
	pthread_mutex_lock(&philo->eat_lock);
	pthread_mutex_lock(&data->write_message);
	printf("\n %ld %i is eating", (get_time_in_ms() - data->start), philo->number);
	pthread_mutex_unlock(&data->write_message);
	pthread_mutex_unlock(&philo->eat_lock);
	ft_sleep(data, data->time_to_eat);
	//usleep(data->time_to_eat * 1000);
	pthread_mutex_lock(&philo->eat_lock);
	philo->last_time_ate = get_time_in_ms();
	pthread_mutex_unlock(&philo->eat_lock);
	pthread_mutex_unlock(&(data->forks[philo->left_fork]));
	pthread_mutex_unlock(&(data->forks[philo->right_fork]));
}

void	philo_eat_right(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	pthread_mutex_lock(&(data->forks[philo->right_fork]));
	pthread_mutex_lock(&data->write_message);
	printf("\n %ld %i has taken right fork", (get_time_in_ms() - data->start), philo->number);
	pthread_mutex_unlock(&data->write_message);
	pthread_mutex_lock(&(data->forks[philo->left_fork]));
	pthread_mutex_lock(&data->write_message);
	printf("\n %ld %i has taken left fork", (get_time_in_ms() - data->start), philo->number);
	pthread_mutex_unlock(&data->write_message);
	pthread_mutex_lock(&philo->eat_lock);
	pthread_mutex_lock(&data->write_message);
	printf("\n %ld %i is eating", (get_time_in_ms() - data->start), philo->number);
	pthread_mutex_unlock(&data->write_message);
	pthread_mutex_unlock(&philo->eat_lock);
	//usleep(data->time_to_eat * 1000);
	ft_sleep(data, data->time_to_eat);
	pthread_mutex_lock(&philo->eat_lock);
	philo->last_time_ate = get_time_in_ms() - philo->data->start;
	pthread_mutex_unlock(&philo->eat_lock);
	pthread_mutex_unlock(&(data->forks[philo->right_fork]));
	pthread_mutex_unlock(&(data->forks[philo->left_fork]));
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
	//usleep(data->time_to_sleep * 1000);
	ft_sleep(data, data->time_to_sleep);
}


void	*philosopher(void *data)
{
	t_philo *philo;
	//t_data	*daata;

	int		i;
	philo = (t_philo *) data;
	//daata = philo->data;
	i = 1;
	while(philo->data->death_check != 1)
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

void	death_checker(t_philo *philo)
{
	t_data	*data;
	int i;

	data = philo->data;
	while (data->death_check != 1)
	{
	i = 0;	
		while(i < data->n_of_philo)
		{
			pthread_mutex_lock(&data->philo[i].eat_lock);
			if (((get_time_in_ms() - data->start) - philo[i].last_time_ate) > data->time_to_die)
			{
				data->death_check = 1;
			}
			if (data->death_check == 1)
			{
					
					pthread_mutex_lock(&data->write_message);
					printf("\n %ld %i died", (get_time_in_ms() - data->start), philo->number);
					pthread_mutex_unlock(&data->write_message);
					break ;
			}
			pthread_mutex_unlock(&data->philo[i].eat_lock);
			//usleep(100);
			i++;
		}
	}
}

void	end_threads_and_mutex(t_data *data)
{
	int i;

	i = 0;
	while (i < data->n_of_philo)
	{
	pthread_join(data->philo[i].philo_thread, NULL);
	pthread_mutex_destroy(&data->forks[i]);
	pthread_mutex_destroy(&data->philo[i].eat_lock);
	i++;
	}
	pthread_mutex_destroy(&data->write_message);
	pthread_mutex_destroy(&data->meal_check);
}

void	simulation(t_data *data)
{
	int	i;
	//int test = 1;

	data->start = get_time_in_ms();
	i = 0;
	while (i < data->n_of_philo)
	{
		pthread_mutex_lock(&data->philo[i].eat_lock);
		data->philo[i].last_time_ate = data->start;
		pthread_mutex_unlock(&data->philo[i].eat_lock);
		pthread_create(&data->philo[i].philo_thread, NULL, philosopher, &data->philo[i]);
		i++;
	}
	//sleep(1000);
	death_checker(data->philo);
	end_threads_and_mutex(data);
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
	ft_init_forks(&data);
	ft_init_philo(&data);
	simulation(&data);
}