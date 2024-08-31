#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*d;
	unsigned char	*s;

	s = (unsigned char *)src;
	d = (unsigned char *)dst;
	if (d == NULL && s == NULL)
		return (NULL);
	if (dst == src)
		return (dst);
	while (n--)
	{
		*d++ = *s++;
	}
	return (dst);
}
