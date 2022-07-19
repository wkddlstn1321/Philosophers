/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: insjang <insjang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 15:49:04 by insjang           #+#    #+#             */
/*   Updated: 2022/07/18 15:49:08 by insjang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include<stdio.h>
# include<pthread.h>
# include<sys/time.h>
# include<stdlib.h>
# include<unistd.h>

typedef pthread_mutex_t	t_pmt;

typedef struct p_philo{
	int				left;
	int				right;
	int				eat_cnt;
	long			last_eat_time;
	pthread_t		philo;
	struct p_info	*info;
}t_philo;

typedef struct p_info{
	int			num;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			must_eat;
	int			die_flag;
	long		start_time;
	int			all_sit_flag;
	t_pmt		write;
	t_pmt		*fork;
	t_philo		*phi;
}t_info;

long		get_time(void);
int			print_error(t_info *info, int i);
int			ft_strlen(const char *s);
int			arg_check(int ac, char **av, t_info *phil);
long		ft_atoi(const char *str);
void		print_act(t_philo *phi, char *str);
void		philo_eat(t_philo *phi);
void		philo_sleep(t_philo *phi);
int			end_check(t_info *info);
#endif
