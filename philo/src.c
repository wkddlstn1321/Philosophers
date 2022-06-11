#include"philosophers.h"

int	ms_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((int)((time.tv_sec * 1000) + (time.tv_usec / 1000)));
}

void	print_act(t_philo *phi, char *str)
{
	int	t;

	t = phi->info->start_time;
	pthread_mutex_lock(&phi->info->write);
	if (!phi->info->die_flag)
		printf("%d %d %s\n", ms_time() - t, phi->left + 1, str);
	pthread_mutex_unlock(&phi->info->write);
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

long long	ft_atoi(const char *str)
{
	int			i;
	long long	atoi;

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