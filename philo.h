/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: delvira- <delvira-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 15:44:14 by delvira-          #+#    #+#             */
/*   Updated: 2023/03/03 15:52:15 by delvira-         ###   ########.fr       */
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
	pthread_mutex_t		left_fork;
	pthread_mutex_t		right_fork;
	struct s_data		*data;
}	t_philo;

typedef struct s_data {
	int				n_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				times_must_eat;
	t_philo			*philo;
	pthread_mutex_t	*forks;
	pthread_mutex_t	write_message;
	pthread_mutex_t	is_eating;
	time_t			start;
}	t_data;

#endif
