#include "philo.h"

long long get_time_now(void)
{
    struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
    // struct timeval tv;
    // long long time;

    // if (gettimeofday(&tv, NULL) != 0)
    //     return(err_msg("Gettimeofday error\n"));
    // printf("gettime_func %lld\n", (tv.tv_sec * 1000 + tv.tv_usec / 1000));
    // time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
    // printf("time val = %lld\n", time);
    // return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
    // return (time);
}

void isleep(long long ms)
{
    long long time_now;

    time_now = get_time_now();
    while (get_time_now() < (time_now + ms))
        usleep(10);
}
