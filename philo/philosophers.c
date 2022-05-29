#include"philosophers.h"

void	*test(void *phil)
{
	(void)phil;
	return (phil);
}

int	main(int argc, char **argv)
{
	if (!(argc == 5 || argc == 6))
	{
		printf("arg error\n");
		return (0);
	}
}
