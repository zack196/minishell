#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*str;
	unsigned char	symbole;

	symbole = (unsigned char)c;
	str = (unsigned char *)s;
	while (n--)
	{
		if (*str == symbole)
			return (str);
		str++;
	}
	return (NULL);
}
