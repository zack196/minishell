#include "../../includes/parse.h"

void    ft_putstr(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        write(1, str + i, 1);
        i++;
    }
}
int check_n(char *str)
{
    int i;

    i = 0;
    if (str[i] == '-')
        i++;
    else
        return (0);
    while (str[i] && str[i] == 'n')
        i++;
    if (!str[i])
        return (1);
    return (0);
}

int    echo(char **av, t_envi **envi)
{
    int i;

    i = 0;
    if (av[i] && check_n(av[i]))
    {
        while (check_n(av[i]))
            i++;
        while (av[i])
            ft_putstr(av[i++]);
    }
    else
    {
        while (av[i])
        {
            ft_putstr(av[i++]);
            if (!av[i])
                break ;
            write(1, " ", 1);
        }
        write(1, "\n", 1);
    }
    set_exit_status(0, envi);
    return (0);
}
