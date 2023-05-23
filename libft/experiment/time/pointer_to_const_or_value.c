#include "exlib.h"

/**
 * @brief
 * Note:
 * 	Compiler optimisation is turned off for this test with -O0
 * 
 * 
 * CONCLUSION:
 * Passing by pointer to const keeps the overhead consistent,
 * although might not be necessary for struct less that or equal to 8 bytes,
 * in theory anyway.
 * 
 * In practice,
 * it should only be impactful under circumstance like, for example,
 * the function is getting called within every iteration in a nested loop,
 * with an actual expensive cost of copy (larger than 32 bytes for example),
 * and might be better off just keep passing it by value other times,
 * not only it's less chance crash yourself with pointers,
 * it can also be more readable without all the pointer arithmetic everywhere.
 * 
 * Something to note is that there is more overhead if the struct is padded
 * (meaning the total size of the members is not divisible by 4)
 */


// typedef double	t_type;
// typedef int	t_type;
// typedef char	t_type;
typedef void*	t_type;

#define	EX_CONST	const

#ifndef EX_CONST
# define EX_CONST
# define NO_CONST
#endif

#define REPEAT	100000000

typedef struct
{
	t_type	a[4];
}			Point;

void	get_value(EX_CONST Point p)
{
	(void)p;
	// p.arr[0] = 39;
}

void	get_pointer(EX_CONST Point *p)
{
	(void)p;
	// p->arr[0] = 39;
}

void	print_value(EX_CONST Point p)
{
	for (unsigned int i = 0; i < sizeof(p.a) / sizeof(p.a[0]); i++)
		printf("%p", &p.a[i]);
	printf("\n");
}

void	print_pointer(EX_CONST Point *p)
{
	for (unsigned int i = 0; i < sizeof(p->a) / sizeof(p->a[0]); i++)
		printf("%p", &p->a[i]);
	printf("\n");
}

void	timetaken_pointer(void (*ft)(EX_CONST Point *), Point *arg)
{
	struct timeval	start;
	struct timeval	end;

	gettimeofday(&start, NULL);
	for (unsigned int i = 0; i < REPEAT; i++)
		ft(arg);
	gettimeofday(&end, NULL);
	dprintf(2, "Time taken pointer: %.3f ms\n", elapsed_time(start, end));
}

void	timetaken_value(void (*ft)(EX_CONST Point), Point arg)
{
	struct timeval	start;
	struct timeval	end;

	gettimeofday(&start, NULL);
	for (int i = 0; i < REPEAT; i++)
		ft(arg);
	gettimeofday(&end, NULL);
	dprintf(2, "Time taken value: %.3f ms\n", elapsed_time(start, end));
}

int	main(void)
{
	Point	p;

	ft_bzero(&p, sizeof(Point));
	timetaken_value(get_value, p);
	timetaken_pointer(get_pointer, &p);

	// timetaken_value(print_value, p);
	// timetaken_pointer(print_pointer, &p);
}
