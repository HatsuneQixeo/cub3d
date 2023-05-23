#include "exlib.h"

typedef struct s_exception
{
	void	*arg;
	t_ftdel	del;
	void	(*what)(void *arg);
}			t_exception;
