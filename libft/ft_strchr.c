#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*str;
	char	symbole;

	str = (char *)s;
	symbole = (char)c;
	while (*str && !(*str == symbole))
		str++;
	if (*str == symbole)
		return (str);
	return (0);
}
