#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include<stdio.h>
# include<pthread.h>
# include<sys/time.h>
# include<stdlib.h>
# include<unistd.h>

typedef pthread_mutex_t	t_pmt;

typedef struct p_philo{
	unsigned int	left;
	unsigned int	right;
	unsigned int	eat_cnt;
	unsigned int	dead;
	pthread_t		philo;
	t_info			*info;
}t_philo;

typedef struct p_info{
	unsigned int	p_arg[5];
	unsigned int	time;
	t_pmt			write;
	t_pmt			*fork;
	t_philo			*phi;
}t_info;
	// unsigned int	p_num;
	// unsigned int	dead;
	// unsigned int	eat;
	// unsigned int	sleep;
	// unsigned int	must_eat;

unsigned int		time_rc(void);
int					prin_error(void);
int					ft_strlen(const char *s);
int					arg_check(int	ac, char **av, t_info *phil);
unsigned long long	ft_atoi(const char *str);
void				prin_act(unsigned int t, t_philo *phi, char *str);

int					philo_eat(t_philo *phi);

#endif