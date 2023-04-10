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
* 1. 파싱
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

* 2. 스레드 생성
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
위 함수는 스레드 생성과 동시에 인자로 받은 start_routine 함수를 생성한 스레드에서 실행시키는데

해당 함수에 인자로 보낼수 있는 값이 마지막 인자인 void *arg 하나밖에 없다.

과제에서는 전역변수가 금지 되기 때문에 새롭게 생성되는 스레드는 main 스레드에서 하나의 인자만을 받아올 수 있는데 이부분에서 고민을 많이 했었다. 

보낼 인자로 파싱 때 미리 저장해 놓은 아래 두개의 구조체가 필요했는데 
```cc
typedef struct p_philo{
	int				left;
	int				right;
	int				eat_cnt;
	long			last_eat_time;
	pthread_t		philo;
}t_philo;
// 각 스레드가 독립적으로 가지고 있을 철학자 한명의 정보

typedef struct p_info{
	int			num;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			must_eat;
	int			die_flag;
	long		start_time;
	t_pmt		write;
	t_pmt		*fork;
	t_pmt		eat_t_check;
	t_pmt		eat_c_check;
	t_pmt		die_check;
	t_pmt		all_seat;
	t_philo		*phi;
}t_info;
// 프로그램 실행할 받은 인자를 파싱한 초기 세팅 값 및 뮤텍스 변수
```

info를 인자로 보내면 각 스레드가 자신이 몇번째 철학자인지 알 수 없고

philo를 인자로 보내면 info에 포함되어 있는 변수들을 사용할 수 없다.

데이터 레이스를 피하기 위해서는 뮤텍스 변수를 반드시 공유할 수 있어야 하기에 info를 보내는 쪽으로 고민하다 

philo 구조체에 info에 주소를 포함하는 변수를 추가하는것으로 간단하게 해결했다.

` struct p_info	*info; // 해당 코드를 philo 구조체에 추가 `



* 3. 스레드 루틴

```cc
void	*rt(void *v_phi)
{
	t_philo	*phi;

	phi = (t_philo *)v_phi;
	pthread_mutex_lock(&phi->info->all_seat);        // 모든 철학자가 착석하기전 의리없이 먼저 식사하는 경우를 방지하기 위한 뮤텍스
	pthread_mutex_unlock(&phi->info->all_seat);      // 스레드 생성 반복문이 끝날 때 메인 스레드에서 언락해준다.
	pthread_mutex_lock(&phi->info->eat_t_check);
	phi->last_eat_time = phi->info->start_time;
	pthread_mutex_unlock(&phi->info->eat_t_check);
	if (phi->left % 2)
	{
		// 철학자 수가 많아도 홀수 번째 철학자가 먼저 식사하는걸 최대한 보장해주기 위한 딜레이 계산 
		if (phi->info->time_to_eat <= 10)
			usleep(phi->info->time_to_eat * 900);
		else
			usleep((phi->info->time_to_eat - 10) * 1000); 
	}
	while (1)
	{
		if (philo_loop(phi))
			break ;
	}
	return (0);
}
```

스레드 생성과 동시에 시작되는 루틴 함수

홀수 번째 철학자가 먼저 식사를 하고 이어서 짝수가 식사를 시작하는게 로직에 핵심이다

이외의 부분은 퍼포먼스 향상을 위한 처리가 대부분

philo_loop 에서 철학자가 죽기 전까지 먹고 자고 생각하는걸 반복하게 구현해줬다.

* 4. 모니터링

```cc
int	end_check(t_info *info)
{
	int		i;

	i = 0;
	while (i < info->num)
	{
		if (info->must_eat != -1)
		{
			if (must_eat_check(info)) // 최소 식사 조건 만족했는지 확인
				return (0);
		}
		if (last_eat_check(info, i))      // 마지막 식사시작 시간 이후 부터 현재까지의 시간을 확인
			return (0);
		i++;
	}
	usleep(50);
	return (1);
}
```

과제 요구사항에 의해 철학자는 다른 철학자들에 죽음을 알 수 없다.
main 스레드에서 각 철학자들에 상태를 모니터링 하다가 사망자 발생시 사망 플래그를 켜준다.

데드락 방지만큼이나 중요한 부분이다 공유자원에 대한 접근이 많다 보니 뮤텍스 변수를 잘 관리해주지 않으면 데이터레이스가 발생하기 쉽다.

출력 부분도 상당한 시간을 투자했었는데 죽음에 대한 출력 이후에 다른 행동들에 대한 출력이 발생해 요구사항에 위배되는 경우가 종종 생겼다.

이론상 출력 이전에 생존 플래그를 미리 확인하고 생존 상태일때만 출력을 하고 출력 전후로 뮤텍스 관리를 해주는데 출력이 섞이는게 의아했었는데

생존 플래그를 통해 생존 상태임을 확인, 이후 행동에 대한 출력 직전에 뮤텍스락이 걸리면 해당 경우가 발생하는걸 확인

이중 뮤텍스 락으로 구현하는걸로 해결했다.

```cc
	//행동에 대한 출력
	pthread_mutex_lock(&phi->info->write);              1 출력 잠금
	pthread_mutex_lock(&phi->info->die_check);          2 생존 플래그 확인
	d = phi->info->die_flag;
	pthread_mutex_unlock(&phi->info->die_check);        2 생존 플래그 확인 후 해제
	if (!d)
		printf("%ld %d %s\n", get_time() - t, phi->left + 1, str);
	pthread_mutex_unlock(&phi->info->write);             1 출력 해제
```




* 5. 스레드 해제
```cc
void	thread_free(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->num)
	{
		pthread_join(info->phi[i].philo, NULL);
		i++;
	}
	i = 0;
	while (i < info->num)
	{
		pthread_mutex_destroy(&info->fork[i]);
		i++;
	}
	pthread_mutex_destroy(&info->write);
	pthread_mutex_destroy(&info->eat_c_check);
	pthread_mutex_destroy(&info->eat_t_check);
	pthread_mutex_destroy(&info->die_check);
	pthread_mutex_destroy(&info->all_seat);
	free(info->phi);
	free(info->fork);
}
```

마지막으로 스레드를 해제해 준다

스레드 해제를 위한 함수는 detach 와 join이 있는데 detach는 빠르고 join은 안전한 느낌이라 join으로 스레드 해제를 해줬다.

