#include"philosophers.h"

static int	range_check(char *str)
{
	long long	num;

	if (ft_strlen(str) > 10)
		return (1);
	num = ft_atoi(str);
	if (num == -1 || num > 4294967295)
		return (1);
	return (0);
}

int	arg_check(int ac, char **av, t_info *info)
{
	int	i;

	i = 1;
	if (ac != 5 && ac != 6)
		return (print_error());
	while (i < 5)
	{
		if (range_check(av[i]))
			return (print_error());
		info->p_arg[i - 1] = ft_atoi(av[i]);
		i++;
	}
	if (ac == 5)
		info->must_eat = -1;
	else
		info->must_eat = ft_atoi(av[5]);
	return (0);
}
