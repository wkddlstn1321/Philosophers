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
	unsigned int	life_time;
	pthread_t		philo;
	struct p_info	*info;
}t_philo;

typedef struct p_info{
	unsigned int	p_arg[4];
	int				must_eat;
	unsigned int	time;
	unsigned int	die_flag;
	t_pmt			write;
	t_pmt			*fork;
	t_philo			*phi;
}t_info;
	// unsigned int	p_num;
	// unsigned int	dead;
	// unsigned int	eat;
	// unsigned int	sleep;
	// unsigned int	must_eat;

unsigned int		ms_time(void);
int					print_error(void);
int					ft_strlen(const char *s);
int					arg_check(int	ac, char **av, t_info *phil);
long long			ft_atoi(const char *str);
void				print_act(t_philo *phi, char *str);

void				philo_eat(t_philo *phi);
void				philo_sleep(t_philo *phi);
void				end_check(t_info *info);
#endif