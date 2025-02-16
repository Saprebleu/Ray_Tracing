#include <stdbool.h>

#include "libft.h"

bool	is_int(const char *s)
{
	int	i;

	i = 0;
	if (s[i] == '-')
		i++;
	if (1 != ft_isdigit(s[i]))
		return (false);
	while (1 == ft_isdigit(s[i]))
		i++;
	return (s[i] == '\0');
}

bool	is_int_in_range(int n, int lower, int upper)
{
	return (n >= lower && n <= upper);
}
