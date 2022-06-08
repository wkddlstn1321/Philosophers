#include"philosophers.h"

void	*rt(void *v_phi)
{
	t_philo	*phi;

	phi = (t_philo *)v_phi;
	while (!phi->info->die_flag)
	{
		philo_eat(phi);
		philo_sleep(phi);
		print_act(phi, "is thinking");
	}
	return (0);
}

int	thread_create(t_info *info)
{
	unsigned int	i;

	i = 0;
	info->time = ms_time();
	info->die_flag = 0;
	while (i < info->p_arg[0])
	{
		info->phi[i].life_time = info->time;
		if (pthread_create(&info->phi[i].philo, NULL, &rt, &info->phi[i]) != 0)
			return (1);
		i++;
	}
	return (0);
}

int	info_init(t_info *info)
{
	unsigned int	i;

	i = 0;
	info->fork = (t_pmt *)malloc(sizeof(t_pmt) * info->p_arg[0]);
	info->phi = (t_philo *)malloc(sizeof(t_philo) * info->p_arg[0]);
	if (info->fork == NULL || info->phi == NULL)
		return (print_error());
	while (i < info->p_arg[0])
	{
		if (pthread_mutex_init(&info->fork[i], NULL) != 0)
			return (print_error());
		info->phi[i].left = i;
		info->phi[i].right = i + 1;
		if (info->phi[i].right == info->p_arg[0])
			info->phi[i].right = 0;
		info->phi[i].eat_cnt = 0;
		info->phi[i].info = info;
		i++;
	}
	if (pthread_mutex_init(&info->write, NULL) != 0)
		return (print_error());
	return (0);
}

int	main(int argc, char **argv)
{
	t_info			info;
	unsigned int	i;

	i = 0;
	if (arg_check(argc, argv, &info))
		return (0);
	if (info_init(&info))
		return (0);
	if (thread_create(&info))
		return (0);
	end_check(&info);
	while (i < info.p_arg[0])
	{
		pthread_join(info.phi->philo, NULL);
		i++;
	}
	i = 0;
	while (i < info.p_arg[0])
	{
		pthread_mutex_destroy(&info.fork[i]);
		i++;
	}
	pthread_mutex_destroy(&info.write);
	free(info.phi);
	free(info.fork);
}
