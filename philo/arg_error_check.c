#include"philosophers.h"

static int	range_check(char *str)
{
	unsigned long long	num;

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
		return (prin_error());
	while (i <= ac)
	{
		if (range_check(av[i]))
			return (prin_error());
		info->p_arg[i - 1] = ft_atoi(av[i]);
		i++;
	}
	if (ac == 5)
		info->p_arg[4] = -1;
	return (0);
}
