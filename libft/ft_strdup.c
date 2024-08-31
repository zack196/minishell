#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*str;

	if(!s1)
	{
		str = malloc(sizeof(char) * 1);
		str[0] = 0;
		return (str);
	}
	str = (char *)malloc(ft_strlen(s1) + 1);
	if (!str)
		return (NULL);
	ft_memcpy(str, s1, ft_strlen(s1) + 1);
	return (str);
}
