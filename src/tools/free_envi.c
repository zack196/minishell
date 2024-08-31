#include "../../includes/parse.h"

void    ft_free_env(t_envi **envi)
{
	t_envi	*tmp1;
	t_envi	*tmp2;

	tmp1 = *envi;
	while (tmp1)
	{
		free(tmp1->key);
		tmp1->key = NULL;
		free(tmp1->value);
		tmp1->value = NULL;
		tmp2 = tmp1->next;
        free(tmp1);
		tmp1 = tmp2;
    }
}