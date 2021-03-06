#include "checker.h"

int		check_sorted(node_a *ptr_a, node_b *ptr_b)
{
	int i;
	int j;

	i = 1;
	while (i <= ptr_a->end)
	{
		j = i;
		while (j > 0)
		{
			if (ptr_a->values[j] < ptr_a->values[j - 1])
				return (0);
			j--;
		}
		i++;
	}
	if (i == ptr_a->end + 1 && ptr_b->end == -1)
		return (1);
	else
		return (0);
}