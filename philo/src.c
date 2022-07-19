/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   src.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: insjang <insjang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 15:49:18 by insjang           #+#    #+#             */
/*   Updated: 2022/07/18 15:49:19 by insjang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philosophers.h"

long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	print_act(t_philo *phi, char *str)
{
	long	t;

	t = phi->info->start_time;
	pthread_mutex_lock(&phi->info->write);
	if (!phi->info->die_flag)
		printf("%ld %d %s\n", get_time() - t, phi->left + 1, str);
	pthread_mutex_unlock(&phi->info->write);
}

int	print_error(t_info *info, int idx)
{
	int	i;

	i = 0;
	if (info->fork != NULL)
	{
		while (i < idx + 1)
		{
			pthread_mutex_destroy(&info->fork[i]);
			i++;
		}
		free(info->fork);
	}
	if (info->phi != NULL)
		free(info->phi);
	printf("error! error!!!!\n");
	return (1);
}

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

long	ft_atoi(const char *str)
{
	int		i;
	long	atoi;

	i = 0;
	atoi = 0;
	if (str[i] == '+')
		i++;
	while ('0' <= str[i] && str[i] <= '9')
	{
		atoi = (atoi * 10) + str[i] - '0';
		i++;
	}
	if (i != ft_strlen(str))
		return (-1);
	return (atoi);
}
