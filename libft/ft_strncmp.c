#include "../minishell.h"

int ft_strncmp(char *s1, char *s2, int n)
{
    while (*s1 && *s2 && *s1 == *s2 && --n)
	{
		s1++;
		s2++;
	}
	return (*s2 - *s1);
}