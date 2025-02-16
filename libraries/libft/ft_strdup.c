#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*cpy;
	size_t	i;

	i = 0;
	cpy = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (cpy == NULL)
		return (NULL);
	while (i < ft_strlen(s))
	{
		cpy[i] = s[i];
		i++;
	}
	cpy[i] = '\0';
	return (cpy);
}
// int main(void)
// {
//     char *truc = ft_strdup("abc");
//     truc[0] = 'P';
//     printf("%s\n", truc);
//     return (0);
// }
