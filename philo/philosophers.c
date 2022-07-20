/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: insjang <insjang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 15:48:48 by insjang           #+#    #+#             */
/*   Updated: 2022/07/18 15:48:49 by insjang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philosophers.h"

void	thread_free(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->num)
	{
		pthread_join(info->phi[i].philo, NULL);
		i++;
	}
	i = 0;
	while (i < info->num)
	{
		pthread_mutex_destroy(&info->fork[i]);
		i++;
	}
	pthread_mutex_destroy(&info->write);
	free(info->phi);
	free(info->fork);
}

void	*rt(void *v_phi)
{
	t_philo	*phi;

	phi = (t_philo *)v_phi;
	while (phi->info->all_sit_flag)
		;
	phi->last_eat_time = phi->info->start_time;
	if (phi->left % 2)
	{
		if (phi->info->time_to_eat <= 10)
			usleep(phi->info->time_to_eat * 900);
		else
			usleep((phi->info->time_to_eat - 10) * 1000);
	}
	while (1)
	{
		pthread_mutex_lock(&phi->info->die_check);
		if (phi->info->die_flag)
			break ;
		pthread_mutex_unlock(&phi->info->die_check);
		philo_eat(phi);
		philo_sleep(phi);
		print_act(phi, "is thinking");
	}
	return (0);
}

int	thread_create(t_info *info)
{
	int	i;

	i = 0;
	info->die_flag = 0;
	while (i < info->num)
	{
		if (pthread_create(&info->phi[i].philo, NULL, &rt, &info->phi[i]) != 0)
			return (1);
		i++;
		usleep(50);
	}
	info->start_time = get_time();
	info->all_sit_flag = 0;
	return (0);
}

int	main(int argc, char **argv)
{
	t_info	info;

	info.fork = NULL;
	info.phi = NULL;
	if (arg_check(argc, argv, &info))
		return (0);
	if (thread_create(&info))
		return (0);
	while (end_check(&info))
		;
	if (info.num == 1)
		pthread_mutex_unlock(&info.fork[0]);
	thread_free(&info);
}
