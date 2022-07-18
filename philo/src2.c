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

void	philo_eat(t_philo *phi)
{
	long	start;

	pthread_mutex_lock(&phi->info->fork[phi->left]);
	print_act(phi, "has taken a fork");
	pthread_mutex_lock(&phi->info->fork[phi->right]);
	print_act(phi, "has taken a fork");
	print_act(phi, "is eating");
	phi->last_eat_time = get_time();
	start = get_time();
	while (get_time() - start < phi->info->time_to_eat)
		usleep(50);
	pthread_mutex_unlock(&phi->info->fork[phi->left]);
	pthread_mutex_unlock(&phi->info->fork[phi->right]);
	if (phi->info->must_eat != -1)
		phi->eat_cnt++;
}

void	philo_sleep(t_philo *phi)
{
	long	start;

	print_act(phi, "is sleeping");
	start = get_time();
	while (get_time() - start < phi->info->time_to_sleep)
		usleep(50);
}

static int	must_eat_check(t_info *info)
{
	int	i;

	i = 0;
	while (info->must_eat <= info->phi[i].eat_cnt)
		i++;
	if (i == info->num)
	{
		info->die_flag = 1;
		return (1);
	}
	return (0);
}

static void	print_die(t_philo *phi)
{
	long	t;

	t = phi->info->start_time;
	pthread_mutex_lock(&phi->info->write);
	phi->info->die_flag = 1;
	printf("%ld %d is died\n", get_time() - t, phi->left + 1);
	pthread_mutex_unlock(&phi->info->write);
}

int	end_check(t_info *info)
{
	int		i;
	long	die_t;

	i = 0;
	die_t = info->time_to_die;
	while (i < info->num)
	{
		if (info->must_eat != -1)
		{
			if (must_eat_check(info))
				return (0);
		}
		if (info->phi[i].last_eat_time > 0)
		{
			if (get_time() - info->phi[i].last_eat_time >= die_t)
			{
				print_die(&info->phi[i]);
				return (0);
			}
		}
		i++;
	}
	usleep(50);
	return (1);
}
