/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: delvira- <delvira-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 15:44:14 by delvira-          #+#    #+#             */
/*   Updated: 2023/06/05 19:14:17 by delvira-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>

typedef struct s_philo {
	int					number;
	pthread_t			philo_thread;
	int					left_fork;
	int					right_fork;
	struct s_data		*data;
	time_t				last_time_ate;
	int					n_of_meals;
}	t_philo;

typedef struct s_data {
	long				n_of_philo;
	long				time_to_die;
	long				time_to_eat;
	long				time_to_sleep;
	long				times_must_eat;
	int					death_check;
	int					all_ate;
	time_t				start;
	pthread_mutex_t		*forks;
	pthread_mutex_t		write_message;
	pthread_mutex_t		eat_lock;
	t_philo				*philo;
}	t_data;

t_data	init_data(char **args);
void	ft_init_forks(t_data *data);
void	ft_init_philo(t_data *data);
long	ft_atoi(const char *str);
int		ft_parse_num(char *str);
int		ft_check_data(char **args);
void	print_message(t_philo *philo, char *message);
time_t	ft_now(void);
time_t	ft_time_diff(time_t past, time_t pre);
void	ft_sleep(t_data *data, time_t sleep);
time_t	get_time_in_ms(void);
void	philo_eat_left(t_philo *philo);
void	philo_eat_right(t_philo *philo);
void	philo_think(t_philo *philo);
void	philo_sleep(t_philo *philo);
void	*philosopher(void *data);
void	line_redu(t_data *data, t_philo *philo, int i);
void	death_checker(t_philo *philo);
void	ft_exit(t_data *data);
void	simulation(t_data *data);
float	grade_to_radian(float grade);

#endif