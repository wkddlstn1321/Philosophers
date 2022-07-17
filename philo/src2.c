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
				if (get_time() - info->phi[i].last_eat_time >= info->time_to_die)
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
