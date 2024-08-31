#include "../../includes/parse.h"

int env(t_envi *envi)
{
    // static  int i;

    // if (!envi)
    //     i = 1;
    // if (i == 1)
    // {
    //     printf("minishell: env: No such file or directory\n");
    //     return ;
    // }
    // g_exit_status = 0;
    while (envi)
    {
        if (ft_strcmp(envi->key, "?") && envi->value)
            printf("%s=%s\n", envi->key, envi->value);
        envi = envi->next;
    }
    return (0);
}