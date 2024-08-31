#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*ptr;
	char	cast;

	ptr = (char *)s + ft_strlen(s);
	cast = (char)c;
	while (ptr >= s)
	{
		if (*ptr == cast)
			return (ptr);
		ptr--;
	}
	return (NULL);
}
