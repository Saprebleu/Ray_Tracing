#include <math.h>
#include <stdbool.h>
#include <stddef.h>

#include "libft.h"

bool	is_double(const char *s)
{
	int	i;

	i = 0;
	if (s[i] == '-')
		i++;
	if (1 != ft_isdigit(s[i]))
		return (false);
	while (1 == ft_isdigit(s[i]))
		i++;
	if (s[i] == '\0')
		return (true);
	if (s[i] != '.')
		return (false);
	i++;
	if (1 != ft_isdigit(s[i]))
		return (false);
	while (1 == ft_isdigit(s[i]))
		i++;
	return (s[i] == '\0');
}

bool	is_double_in_range(double n, double lower, double upper)
{
	return (fmax(n, lower) == n && fmin(n, upper) == n);
}

int	ft_strclen(const char *s, char c)
{
	char	*tmp;

	tmp = ft_strchr(s, c);
	if (tmp == NULL)
		return (ft_strlen(s));
	return (tmp - s);
}

double	get_double(const char *s)
{
	int		sign;
	double	n;
	double	decimals;
	int		i;

	sign = 1;
	if (s[0] == '-')
		sign = -1;
	n = ft_atoi(s);
	decimals = 0;
	i = 0;
	while (s[i] && (ft_isdigit(s[i]) == 1 || s[i] == '-'))
	{
		if (s[i] == '.')
			break ;
		i++;
	}
	if (s[i] != '.')
		return (n);
	decimals = ft_atoi(s + i + 1);
	return (n + (sign
			* (decimals / (double)pow(10, ft_strclen(s + i + 1, ',')))));
}
