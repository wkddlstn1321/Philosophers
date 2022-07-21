/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   src2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: insjang <insjang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 15:49:27 by insjang           #+#    #+#             */
/*   Updated: 2022/07/18 15:49:29 by insjang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philosophers.h"

static void	print_die(t_philo *phi)
{
	long	t;

	t = phi->info->start_time;
	pthread_mutex_lock(&phi->info->die_check);
	phi->info->die_flag = 1;
	pthread_mutex_unlock(&phi->info->die_check);
	pthread_mutex_lock(&phi->info->write);
	printf("%ld %d is died\n", get_time() - t, phi->left + 1);
	pthread_mutex_unlock(&phi->info->write);
}

static int	last_eat_check(t_info *info, int i)
{
	long	eat_t;
	long	die_t;

	die_t = info->time_to_die;
	pthread_mutex_lock(&info->eat_t_check);
	eat_t = info->phi[i].last_eat_time;
	pthread_mutex_unlock(&info->eat_t_check);
	if (eat_t > 0)
	{
		if (get_time() - eat_t >= die_t)
		{
			print_die(&info->phi[i]);
			return (1);
		}
	}
	return (0);
}

static int	must_eat_check(t_info *info)
{
	int	i;
	int	eat;

	i = 0;
	while (i < info->num)
	{
		pthread_mutex_lock(&info->eat_c_check);
		eat = info->phi[i].eat_cnt;
		pthread_mutex_unlock(&info->eat_c_check);
		if (info->must_eat > eat)
			break ;
		i++;
	}
	if (i == info->num)
	{
		pthread_mutex_lock(&info->die_check);
		info->die_flag = 1;
		pthread_mutex_unlock(&info->die_check);
		return (1);
	}
	return (0);
}

int	end_check(t_info *info)
{
	int		i;

	i = 0;
	while (i < info->num)
	{
		if (info->must_eat != -1)
		{
			if (must_eat_check(info))
				return (0);
		}
		if (last_eat_check(info, i))
			return (0);
		i++;
	}
	usleep(50);
	return (1);
}
