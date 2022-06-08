#include"philosophers.h"

void	philo_eat(t_philo *phi)
{
	unsigned int	start;
	int				info_time;

	info_time = phi->info->time;
	pthread_mutex_lock(&phi->info->fork[phi->left]);
	print_act(phi, "has taken a fork");
	pthread_mutex_lock(&phi->info->fork[phi->right]);
	print_act(phi, "has taken a fork");
	print_act(phi, "is eating");
	start = ms_time();
	while (!phi->info->die_flag)
	{
		if (ms_time() - start <= phi->info->p_arg[2])
		{
			if (phi->info->must_eat != -1)
				phi->eat_cnt++;
			phi->life_time = ms_time();
			break ;
		}
	}
	pthread_mutex_unlock(&phi->info->fork[phi->left]);
	pthread_mutex_unlock(&phi->info->fork[phi->right]);
}

void	philo_sleep(t_philo *phi)
{
	unsigned int	start;
	int				info_time;

	info_time = phi->info->time;
	print_act(phi, "is sleeping");
	start = ms_time();
	while (!phi->info->die_flag)
	{
		if (ms_time() - start <= phi->info->p_arg[3])
			break ;
	}
}

static int	must_eat_check(t_info *info)
{
	unsigned int	i;

	i = 0;
	while (info->must_eat <= (int)info->phi[i].eat_cnt)
		i++;
	if (i == info->p_arg[0])
	{
		info->die_flag = 1;
		return (1);
	}
	return (0);
}

void	end_check(t_info *info)
{
	unsigned int	i;

	i = 0;
	while (i < info->p_arg[0])
	{
		if (must_eat_check(info))
			return ;
		if (info->phi[i].life_time - ms_time() <= info->p_arg[1])
		{
			print_act(&info->phi[i], "is died");
			info->die_flag = 1;
			break ;
		}
		i++;
		if (i == info->p_arg[0])
			i = 0;
	}
}
