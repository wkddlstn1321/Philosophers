#include"philosophers.h"

int	philo_loop(t_philo *phi)
{
	int	t;

	pthread_mutex_lock(&phi->info->die_check);
	t = phi->info->die_flag;
	pthread_mutex_unlock(&phi->info->die_check);
	if (t)
		return (1);
	philo_eat(phi);
	philo_sleep(phi);
	print_act(phi, "is thinking");
	return (0);
}

void	philo_eat(t_philo *phi)
{
	long	start;

	pthread_mutex_lock(&phi->info->fork[phi->left]);
	print_act(phi, "has taken a fork");
	pthread_mutex_lock(&phi->info->fork[phi->right]);
	print_act(phi, "has taken a fork");
	print_act(phi, "is eating");
	pthread_mutex_lock(&phi->info->eat_t_check);
	phi->last_eat_time = get_time();
	pthread_mutex_unlock(&phi->info->eat_t_check);
	start = get_time();
	while (get_time() - start < phi->info->time_to_eat)
		usleep(50);
	pthread_mutex_unlock(&phi->info->fork[phi->left]);
	pthread_mutex_unlock(&phi->info->fork[phi->right]);
	if (phi->info->must_eat != -1)
	{
		pthread_mutex_lock(&phi->info->eat_c_check);
		phi->eat_cnt++;
		pthread_mutex_unlock(&phi->info->eat_c_check);
	}
}

void	philo_sleep(t_philo *phi)
{
	long	start;

	print_act(phi, "is sleeping");
	start = get_time();
	while (get_time() - start < phi->info->time_to_sleep)
		usleep(50);
}

void	print_act(t_philo *phi, char *str)
{
	long	t;
	int		d;


	t = phi->info->start_time;
	
	pthread_mutex_lock(&phi->info->die_check);
	d = phi->info->die_flag;
	pthread_mutex_unlock(&phi->info->die_check);
	pthread_mutex_lock(&phi->info->write);
	if (!d)
		printf("%ld %d %s\n", get_time() - t, phi->left + 1, str);
	pthread_mutex_unlock(&phi->info->write);
}