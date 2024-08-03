#include "../minishell.h"

void    _env(t_minishell *sh)
{
    t_env   *env;

    env = sh->env;
    print_env(env, 0);
}