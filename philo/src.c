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

int	print_error(t_info *info)
{
	if (info->fork != NULL)
		free(info->fork);
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
