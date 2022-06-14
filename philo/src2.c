#include"philosophers.h"

void	philo_eat(t_philo *phi, int i, int j)
{
	int	start;

	pthread_mutex_lock(&phi->info->fork[i]);
	print_act(phi, "has taken a fork");
	pthread_mutex_lock(&phi->info->fork[j]);
	print_act(phi, "has taken a fork");
	print_act(phi, "is eating");
	phi->last_eat_time = ms_time();
	start = ms_time();
	while (!phi->info->die_flag)
	{
		if (ms_time() - start >= phi->info->time_to_eat)
		{
			if (phi->info->must_eat != -1)
				phi->eat_cnt++;
			break ;
		}
		usleep(50);
	}
	pthread_mutex_unlock(&phi->info->fork[i]);
	pthread_mutex_unlock(&phi->info->fork[j]);
}

void	philo_sleep(t_philo *phi)
{
	int	start;

	print_act(phi, "is sleeping");
	start = ms_time();
	while (!phi->info->die_flag)
	{
		if (ms_time() - start >= phi->info->time_to_sleep)
			break ;
		usleep(50);
	}
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

void	end_check(t_info *info)
{
	int	i;

	while (1)
	{
		i = 0;
		while (i < info->num)
		{
			if (info->must_eat != -1)
			{
				if (must_eat_check(info))
					return ;
			}
			if (info->phi[i].last_eat_time > 0)
			{
				if (ms_time() - info->phi[i].last_eat_time >= info->time_to_die)
				{
					print_act(&info->phi[i], "is died");
					info->die_flag = 1;
					return ;
				}
			}
			i++;
		}
		usleep(50);
	}
}
