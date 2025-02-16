#include "get_next_line.h"

size_t	ft_strlen2(const char *s)
{
	size_t	length;

	length = 0;
	if (s == NULL)
		return (0);
	while (*s)
	{
		length++;
		s++;
	}
	return (length);
}

char	*ft_strdup2(char *s)
{
	size_t	len;
	size_t	i;
	char	*s_cpy;

	i = 0;
	len = ft_strlen2(s) + 1;
	if (s == NULL)
		return (NULL);
	s_cpy = malloc(len);
	if (s_cpy == NULL)
		return (NULL);
	while (s[i] != '\0')
	{
		s_cpy[i] = s[i];
		i++;
	}
	s_cpy[i] = '\0';
	return (s_cpy);
}

char	*ft_strlcpy2(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		dst[i] = src[i];
		i++;
	}
	return (dst);
}

char	*begins_after_n(char *s)
{
	int		i;
	char	*cpy;

	i = 0;
	if (s == NULL)
		return (NULL);
	while (s[i])
	{
		if (s[i] == '\n')
			break ;
		i++;
	}
	cpy = ft_strdup2(s + i + 1);
	return (cpy);
}

int	n_is_nth_char_of(char *str)
{
	int	count;
	int	i;

	count = 1;
	i = 0;
	while (str[i] != '\n')
	{
		count++;
		i++;
	}
	return (count);
}
