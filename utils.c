#include "minishell.h"

char    *ft_strdup_mod(char *str, t_shell *shell)
{
    int     i;
    char    *res;

    i = 0;
    while (str[i] && str[i] != '=')
        i++;
    res = my_malloc(i + 1, shell);
    i = 0;
    while (str[i] && str[i] != '=')
    {
        res[i] = str[i];
        i++;        
    }
    res[i] = '\0';
    return (res);
}
