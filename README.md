# Philosophers
식사하는 철학자 문제
https://ko.wikipedia.org/wiki/%EC%8B%9D%EC%82%AC%ED%95%98%EB%8A%94_%EC%B2%A0%ED%95%99%EC%9E%90%EB%93%A4_%EB%AC%B8%EC%A0%9C

---
식사하는 철학자 문제를 통해 프로세스 스레딩을 다루는 방법을 익히는 과제로
과제의 요구사항과 필요한 개념 지식들은 아래 링크에 정리해 뒀다.

https://www.notion.so/Philosophers-cd0252edca9a476bac92f4dd9d37bc00

문제를 해결하는 방법은 생각보다 간단하다.
일정한 방향으로 철학자들에게 순서대로 번호를 부여하고 해당 번호가 홀수 또는 짝수인 철학자들이 먼저 식사를 하게 하면 규착 상태 발생 필수 조건중 하나인 점유대기를 방지함으로 교착 상태를 막을 수 있다.

### 1. 파싱
```
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
