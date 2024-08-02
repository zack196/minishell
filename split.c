#include"parser.h"
static int	count(char const *s, char c)
{
	int	i;
	int	r;

	i = 0;
	r = 0;
	if (s[i] == '\0')
		return (0);
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i])
			r++;
		while (s[i] != c && s[i])
			i++;
	}
	return (r);
}

static int	longklma(char const *s, char c)
{
	int	word;
	int	i;

	i = 0;
	word = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		while (s[i] && s[i] != c)
		{
			word++;
			i++;
		}
		if (s[i - 1] != c)
			return (word);
	}
	return (0);
}

static char	**freedd(char **res)
{
	int	i;

	i = 0;
	if (res)
	{
		while (res[i])
		{
			free(res[i]);
			i++;
		}
		free(res);
	}
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**res;
	int		j;

	j = 0;
	if (s == 0)
		return (0);
	res = malloc((count(s, c) + 1) * sizeof(char *));
	if (res == 0)
		return (free(res), NULL);
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
		{
			res[j] = ft_substr(s, 0, longklma(s, c));
			if (!res[j])
				return (freedd(res));
			s += longklma(s, c);
			j++;
		}
	}
	res[j] = NULL;
	return (res);
}