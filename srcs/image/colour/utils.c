void	ft_intset(int *arr, const unsigned int size, const int value)
{
	unsigned int	i;

	i = -1;
	while (++i < size)
		arr[i] = value;
}
