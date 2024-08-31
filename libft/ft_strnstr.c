#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	char	*str;
	char	*to_find;
	size_t	i;
	size_t	j;

	str = (char *)haystack;
	to_find = (char *)needle;
	i = 0;
	j = 0;
	if (to_find[j] == '\0')
		return (str);
	while (str[i] && i < len)
	{
		j = 0;
		while (str[i + j] == to_find[j] && str[i + j] != '\0' && (i + j < len))
			j++;
		if (to_find[j] == '\0')
			return (str + i);
		i++;
	}
	return (0);
}
