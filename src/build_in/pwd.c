#include "../../includes/parse.h"

char    *get_pwd(t_envi *envi, int *i)
{
    char    *pwd;
    t_envi    *env_pwd;
    char    buff[PATH_MAX];

    pwd = getcwd(buff, PATH_MAX);
    if (!pwd)
    {
        env_pwd = find_node(envi, "PWD");
        if (env_pwd)
            pwd = env_pwd->value;
        if (!pwd)
        {
            perror("PWD ");// ta tchof chi error message 7san
            set_exit_status(1, &envi);
            *i = 1;
            return (NULL);
        }
    }
    *i = 0;
    return (ft_strdup(pwd));
}

int	pwd(t_envi *envi)
{
    char    *pwd;
    int     exit_stat;

    pwd = get_pwd(envi, &exit_stat);
    if (pwd)
        printf("%s\n", pwd);
    free(pwd);
    return (exit_stat);
}
