#include "checker.h"

static void		free_memory(char **s)
{
	int i;

	i = 0;
	while (s[i])
		free(s[i++]);
	free(s[i]);
	free(s);
}

static int		compare_elements(int i, char *s)
{
	char *temp_val;

	temp_val = NULL;
	temp_val = ft_itoa(i);
	if (ft_strcmp(temp_val, s) != 0)
	{
		free(temp_val);
		return (1);
	}
	free(temp_val);
	return (0);
}

static int		return_size(int argc, char **argv)
{
	int		size;
	int		i;
	int		j;
	int		k;
	char	**s;

	size = 0;
	k = 0;
	i = 1;
	while (i < argc)
	{
		s = ft_strsplit(argv[i], ' ');
		j = 0;
		while (s[j])
		{
			k = ft_atoi(s[j]);
			if (compare_elements(k, s[j]))
				return (0);
			j++;
			size++;
		}
		free_memory(s);
		i++;
	}
	return (size);
}

static int		assign_array_values(int argc, char **argv, node_a *ptr_a)
{
	int		i;
	int		j;
	int		k;
	char	**s;
	int		max_int = 2147483647;
	int		tmp_val;

	k = 0;
	i = 1;
	ptr_a->values = (int *)malloc(sizeof(int) * ptr_a->max_size);
	while (i < argc)
	{
		s = ft_strsplit(argv[i], ' ');
		j = 0;
		while (s[j])
		{
			tmp_val = ft_atoi(s[j]);
			ptr_a->values[k] = ft_atoi(s[j]);
			if (compare_elements(ptr_a->values[k], s[j]) || max_int == tmp_val)
				return (0);
			k++;
			j++;
		}
		free_memory(s);
		i++;
	}
	return (1);
}

int				main(int argc, char **argv)
{
	int		size;
	int		i;
	node_a	ptr_a;
	node_b	ptr_b;

	if (argc >= 2)
	{
		if ((size = return_size(argc, argv)))
		{
			stack_ab(&ptr_a, &ptr_b, size);
			assign_array_values(argc, argv, &ptr_a);
			ptr_a.end = ptr_a.max_size - 1;
			i = evaluate_commands(&ptr_a, &ptr_b);
			if (i == 1)
				write(1, "OK\n", 3);
			else if (i == 2)
				write(2, "Error\n", 6);
			else if(i == 0)
				write(2, "KO\n", 3);
		}
		else
			write(2, "Error\n", 6);
	}
	return (0);
}