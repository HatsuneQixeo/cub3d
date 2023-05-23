#include "exlib.h"

double	elapsed_time(struct timeval start, struct timeval end)
{
	const double	seconds = (end.tv_sec - start.tv_sec);
	const double	microseconds = (end.tv_usec - start.tv_usec);

	return ((seconds * 1000) + (microseconds / 1000));
}

void	*time_debug(const char *prefix, void *(*ft)(void *), void *arg)
{
	struct timeval	start;
	struct timeval	end;
	void			*ret;

	gettimeofday(&start, NULL);
	ret = ft(arg);
	gettimeofday(&end, NULL);
	dprintf(2, "%s: %.3f ms\n", prefix, elapsed_time(start, end));
	return (ret);
}
