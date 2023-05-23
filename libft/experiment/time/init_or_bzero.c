#include "libft.h"
#include <string.h>
#include <sys/time.h>

typedef struct
{
	int	x;
	int	y;
}		Point;

double	elapsed(const struct timeval start, const struct timeval end)
{
	return (((end.tv_sec - start.tv_sec) * 1000)
		+ ((end.tv_usec - start.tv_usec) * .0001));
}

int	main(void)
{
	const unsigned int	limit = 100;
	Point	p[1000000];
	struct timeval	start;
	struct timeval	end;
	double			passed;

	// {
	// 	gettimeofday(&start, NULL);
	// 	for (unsigned int i = 0; i < limit; i++)
	// 		p = (Point[]){0};
	// 	gettimeofday(&end, NULL);
	// }
	// passed = elapsed(start, end);
	// printf("{0}: %f\n", passed);

	{
		gettimeofday(&start, NULL);
		for (unsigned int i = 0; i < limit; i++)
			bzero(&p, sizeof(p));
		gettimeofday(&end, NULL);
	}
	passed = elapsed(start, end);
	printf("bzero: %f\n", passed);

	{
		gettimeofday(&start, NULL);
		for (unsigned int i = 0; i < limit; i++)
			ft_bzero(&p, sizeof(p));
		gettimeofday(&end, NULL);
	}
	passed = elapsed(start, end);
	printf("ft_bzero: %f\n", passed);

}
