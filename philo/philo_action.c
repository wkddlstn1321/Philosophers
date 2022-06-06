#include"philosophers.h"

int	philo_eat(t_philo *phi)
{
	pthread_mutex_lock(&phi->info->fork[phi->left]);
	prin_act(10, phi, "has taken a fork");
	pthread_mutex_lock(&phi->info->fork[phi->right]);
	prin_act(10, phi, "has taken a fork");

	prin_act(10, phi, "is eating");
	phi->eat_cnt++;
	pthread_mutex_unlock(&phi->info->fork[phi->left]);
	pthread_mutex_unlock(&phi->info->fork[phi->right]);
}
