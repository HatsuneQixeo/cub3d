#include "cubmap.h"

const char	*set_wall(void)
{
	static const char	arr[] = {Wall, '\0'};

	return (arr);
}

const char	*set_door(void)
{
	static const char	arr[] = {Wall, DoorClose, '\0'};

	return (arr);
}

const char	*set_any(void)
{
	static const char	arr[] = {Wall, DoorClose, DoorOpen, '\0'};

	return (arr);
}
