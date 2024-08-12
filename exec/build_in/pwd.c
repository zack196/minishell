#include "../../minishell.h"
void    pwd(void)
{
    char    path_name[PATH_MAX];

    if (!getcwd(path_name, PATH_MAX))
    {
        perror("path_problem\n"); // chof ach khas yataktab hna!!!
        exit(1);
    }
    //handel if it depass MAX_PATH
    printf("%s\n", path_name);
}