#include"philosophers.h"

void	thread_free(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->num)
	{
		pthread_join(info->phi->philo, NULL);
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
	int		i;
	int		j;

	phi = (t_philo *)v_phi;
	while (phi->info->all_sit_flag)
		;
	phi->last_eat_time = phi->info->start_time;
	i = phi->left;
	j = phi->right;
	if (phi->left % 2)
	{
		usleep(50);
		i = phi->right;
		j = phi->left;
	}
	while (!phi->info->die_flag)
	{
		philo_eat(phi, i, j);
		philo_sleep(phi);
		print_act(phi, "is thinking");
		if (phi->info->num % 2)
			usleep(50);
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
	info->start_time = ms_time();
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
	if (info.must_eat == 0)
	{
		free(info.phi);
		free(info.fork);
		return (0);
	}
	if (thread_create(&info))
		return (0);
	end_check(&info);
	if (info.num == 1)
		pthread_mutex_unlock(&info.fork[0]);
	thread_free(&info);
}
