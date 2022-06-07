#include"philosophers.h"

int	r_t(t_philo *phi)
{
	while (phi->dead > 0)
	{
		philo_eat(phi);
		philo_sleep(phi);
		philo_think(phi);
	}
	philo_dead(phi);
}

int	thread_create(t_info *info)
{
	int	i;

	i = 0;
	info->time = time_rc();
	while (i < info->p_arg[0])
	{
		if (pthread_create(info->phi[i].philo, NULL, &r_t, &info->phi[i]) != 0)
			return (1);
	}
	return (0);
}

int	info_init(t_info *info)
{
	int	i;

	info->fork = (t_pmt *)malloc(sizeof(t_pmt) * info->p_arg[0]);
	info->phi = (t_philo *)malloc(sizeof(t_philo) * info->p_arg[0]);
	if (info->fork == NULL || info->phi == NULL)
		return (prin_error());
	while (i < info->p_arg[0])
	{
		if (pthread_mutex_init(&info->fork[i], NULL) != 0)
			return (prin_error());
		info->phi[i].left = i;
		info->phi[i].right = i + 1;
		if (info->phi[i].right == info->p_arg[0])
			info->phi[i].right = 0;
		info->phi[i].eat_cnt = 0;
		info->phi[i].dead = 0;
		info->phi[i].info = info;
		i++;
	}
	if (pthread_mutex_init(&info->write, NULL) != 0)
		return (prin_error());
	return (0);
}

int	main(int argc, char **argv)
{
	t_info			info;
	int				i;

	if (arg_check(argc, argv, &info))
		return (0);
	if (info_init(&info))
		return (0);
	if (thread_create(&info))
		return (0);
}
