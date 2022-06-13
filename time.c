#include "philo.h"

unsigned long long get_time_now(void)
{
    struct timeval tv;

    if (gettimeofday(&tv, NULL) != 0)
        return(return_error("Gettimeofday error\n"));
    return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}
