/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: delvira- <delvira-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 18:36:29 by delvira-          #+#    #+#             */
/*   Updated: 2023/03/17 18:37:14 by delvira-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
		usleep(50);
	}
}

time_t	get_time_in_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}
