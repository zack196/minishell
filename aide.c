#include "parser.h"
int	ft_strchr_2(const char *str, int c)
{
	char			*ptr;
	int				i;
	unsigned char	ch;

	i = 0;
	ptr = (char *)str;
	ch = c;
	if (!str)
		return (0);
	while (ptr[i])
	{
		if (ptr[i] == ch)
			return (i);
		i++;
	}
	if (ptr[i] == ch)
		return (i);
	return (0);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t			i;
	unsigned char	*str1;
	unsigned char	*str2;

	i = 0;
	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	if (!str1 || !str2)
		return (0);
	while (s1[i] && s2[i])
	{
		if (str1[i] != str2[i])
			break ;
		i++;
	}	
	if (str1[i] > str2[i])
		return (1);
	else if (str1[i] < str2[i])
		return (-1);
	return (0);
}

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

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = ft_strlen(src);
	if (dstsize == 0)
		return (j);
	while (*(src + i) && i < dstsize - 1)
	{
		*(dst + i) = *(src + i);
		i++;
	}
	*(dst + i) = '\0';
	return (j);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	char	*dup;

	str = (char *)s;
	if (!str)
		return (NULL);
	if (start > ft_strlen(str))
		return (ft_strdup(""));
	if (len > ft_strlen(str + start))
	{
		dup = malloc(ft_strlen(str + start) + 1);
		len = ft_strlen(str + start);
	}
	else
		dup = malloc(len + 1);
	if (!dup)
		return (NULL);
	ft_strlcpy(dup, str + start, len + 1);
	return (dup);
}


int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*str1;
	unsigned char	*str2;

	i = 0;
	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	if (n == 0)
		return (0);
	while (i < n && s1[i] && s2[i])
	{
		if (str1[i] != str2[i])
			break ;
		i++;
	}	
	if (i >= n)
		i--;
	if (str1[i] > str2[i])
		return (1);
	else if (str1[i] < str2[i])
		return (-1);
	return (0);
}
size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (!s || !*s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

void	ft_putstr_fd(char *s, int fd)
{
	if (s)
		write(fd, s, ft_strlen(s));
}

void	to_exit(void)
{
	ft_putstr_fd("exit\n", 2);
	exit(1);
}

int	is_all_spaces(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if ((str[i] != ' ' || str[i] != '\n' || str[i] != '\t'))
			return (0);
		i++;
	}
	return (1);
}