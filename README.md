# Philosophers
식사하는 철학자 문제
https://ko.wikipedia.org/wiki/%EC%8B%9D%EC%82%AC%ED%95%98%EB%8A%94_%EC%B2%A0%ED%95%99%EC%9E%90%EB%93%A4_%EB%AC%B8%EC%A0%9C

---
식사하는 철학자 문제를 통해 프로세스 스레딩을 다루는 방법을 익히는 과제로

해당 과제의 요구사항과 필요한 개념 지식들은 아래 링크에 정리해 뒀다.

https://www.notion.so/Philosophers-cd0252edca9a476bac92f4dd9d37bc00

문제를 해결하는 방법은 생각보다 간단하다.
일정한 방향으로 철학자들에게 순서대로 번호를 부여하고 해당 번호가 홀수 또는 짝수인 철학자들이 먼저 식사를 하게 하면 규착 상태 발생 필수 조건중 하나인 점유대기를 방지함으로 교착 상태를 막을 수 있다.

### 코드 흐름 
1. 파싱
```cc
// 파싱 코드중 일부
info->num = ft_atoi(av[1]);
if (info->num < 1)
	return (print_error(info));
info->time_to_die = ft_atoi(av[2]);
info->time_to_eat = ft_atoi(av[3]);
info->time_to_sleep = ft_atoi(av[4]);
if (ac == 5)
	info->must_eat = -1;
else
	info->must_eat = ft_atoi(av[5]);
if (info->must_eat == 0)
	return (1);
return (info_init(info));
...
```
파싱 부분은 어렵지 않다. 들어 오는 인자에 대해서 처리하면 되는 비교적 간단한 부분

2. 스레드 생성
```cc
int	thread_create(t_info *info)
{
	int	i;

	i = 0;
	info->die_flag = 0;
	pthread_mutex_lock(&info->all_seat);
	while (i < info->num)
	{
		if (pthread_create(&info->phi[i].philo, NULL, &rt, &info->phi[i]) != 0)
			return (print_error(info));
		i++;
	}
	info->start_time = get_time();
	pthread_mutex_unlock(&info->all_seat);
	return (0);
}
```
구현하기가 생각보다 까다로웠던 부분인데 그 이유는 pthread_create 함수 때문이다.

```cc
int pthread_create(pthread_t *thread, const pthread_attr_t *arr, void *(*start_routine(void *), void *arg)
```
위 함수는 스레드 생성과 동시에 인자로 받은 start_routine 함수를 생성한 스레드에서 실행시키는데 해당 함수에 인자로 보낼수 있는 값이 하나밖에 없다.
과제에서는 전역변수가 금지 되기 때문에 새롭게 생성되는 스레드는 main 스레드에서 하나의 인자만을 받아올 수 있는데 이부분에서 고민을 많이 했었다. 

