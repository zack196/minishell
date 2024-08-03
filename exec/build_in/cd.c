#include "../../minishell.h"

void    cd(const char *path)
{
    if (chdir(path) && *path)
    {
        path = ft_strjoin("bash: cd: ", path);
        perror(path);
    }
}