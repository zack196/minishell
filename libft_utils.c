#include "minishell.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (*str)
	{
		str++;
		i++;
	}
	return (i);
}

char	*ft_strdup(const char *s1, t_shell *shell)
{
	char	*res;
	int		i;

	res = (char *)my_malloc(ft_strlen(s1) + 1, shell);
	i = 0;
	if (!res)
		return (0);
	while (*s1)
	{
		res[i] = *s1;
		s1++;
		i++;
	}
	res[i] = '\0';
	return (res);
}

char	*ft_strjoin(char const *s1, char const *s2, t_shell *shell)
{
	char	*res;
	int		i;

	if (!s1 || !s2)
		return (NULL);
	res = (char *)my_malloc(ft_strlen(s1) + ft_strlen(s2) + 1, shell);
	i = 0;
	if (!res)
		return (NULL);
	while (s1[i])
	{
		res[i] = s1[i];
		i++;
	}
	while (s2[i - ft_strlen(s1)])
	{
		res[i] = s2[i - ft_strlen(s1)];
		i++;
	}
	res[i] = 0;
	return (res);
}