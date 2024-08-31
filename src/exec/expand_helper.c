#include "../../includes/parse.h"


int ptr_size(char **ptr)
{
    int i;

    if (!ptr)
		return (0);
	i = 0;
    while (ptr[i])
        i++;
    return (i);
}

char    **append_char(char **ptr1, char **ptr2)
{
	char	**res;
	int		size;
	int		i;
	int		j;

	size = ptr_size(ptr1) + ptr_size(ptr2);
	res = malloc((size + 1) * sizeof (char *));
	if (!res)
		return (NULL);
	i = -1;
	while (ptr1 && ptr1[++i])
	{
		res[i] = ft_strdup(ptr1[i]);
	}
	j = -1;
    while (ptr2 && ptr2[++j])
		res[i++] = ft_strdup(ptr2[j]);
	res[i] = NULL;
	i = -1;
	while (ptr1[++i])
		free(ptr1[i]);
	i = -1;
	while (ptr2[++i])
		free(ptr2[i]);
	return (free(ptr1), res);
}

char    **split_space(char **ptr)
{
    char    **res;
	char	**tmp;
	int		i;

	i = -1;
	res = malloc(sizeof (char *));
	if (!res)
		return NULL;
	res[0] = NULL;
	while (ptr[++i])
	{
		tmp = ft_split(ptr[i], ' ');
		res = append_char(res, tmp);
	}
	free(tmp);
	return (res);
}