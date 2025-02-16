#include "libft.h"

int	ft_isalnum(int argument)
{
	if ((argument >= 'A' && argument <= 'Z')
		|| (argument >= 'a' && argument <= 'z')
		|| (argument >= '0' && argument <= '9'))
		return (1);
	return (0);
}
