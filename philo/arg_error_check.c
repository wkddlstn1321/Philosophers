#include"philosophers.h"

int	info_init(t_info *info)
{
	int	i;

	i = 0;
	info->fork = (t_pmt *)malloc(sizeof(t_pmt) * info->num);
	info->phi = (t_philo *)malloc(sizeof(t_philo) * info->num);
	if (info->fork == NULL || info->phi == NULL)
		return (print_error(info));
	while (i < info->num)
	{
		if (pthread_mutex_init(&info->fork[i], NULL) != 0)
			return (print_error(info));
		info->phi[i].left = i;
		info->phi[i].right = i + 1;
		if (info->phi[i].right == info->num)
			info->phi[i].right = 0;
		info->phi[i].eat_cnt = 0;
		info->phi[i].info = info;
		i++;
	}
	info->all_sit_flag = 1;
	if (pthread_mutex_init(&info->write, NULL) != 0)
		return (print_error(info));
	return (0);
}

static int	range_check(char *str)
{
	long long	num;

	if (ft_strlen(str) > 10)
		return (1);
	num = ft_atoi(str);
	if (num == -1 || num > 2147483647)
		return (1);
	return (0);
}

int	arg_check(int ac, char **av, t_info *info)
{
	int	i;

	if (ac != 5 && ac != 6)
		return (print_error(info));
	i = 1;
	while (i < ac)
	{
		if (range_check(av[i]))
			return (print_error(info));
		i++;
	}
	info->num = ft_atoi(av[1]);
	info->time_to_die = ft_atoi(av[2]);
	info->time_to_eat = ft_atoi(av[3]);
	info->time_to_sleep = ft_atoi(av[4]);
	if (ac == 5)
		info->must_eat = -1;
	else
		info->must_eat = ft_atoi(av[5]);
	return (info_init(info));
}
