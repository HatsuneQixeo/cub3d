#ifndef EXLIB_H
# define EXLIB_H

# include "libft.h"
# include <sys/time.h>

# ifndef BENCHMARK
#  define BENCHMARK	0
# endif

# if BENCHMARK != 0
#  define TIME(prefix, expression)	({ \
	struct timeval	__start__; \
	struct timeval	__end__; \
\
	gettimeofday(&__start__, NULL); \
	expression; \
	gettimeofday(&__end__, NULL); \
	printf("%s: %.3f ms\n", prefix, elapsed_time(__start__, __end__)); \
})
# else
#  define TIME(prefix, expression)	expression;
# endif

# define BENCHMARK_MSG(msg)	if (BENCHMARK) printf(#msg"\n")

double	elapsed_time(struct timeval start, struct timeval end);
void	*time_debug(const char *prefix, void *(*ft)(void *), void *arg);

#endif
