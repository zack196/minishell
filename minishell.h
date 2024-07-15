#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>


typedef struct s_heap
{
	void			*p_content;
	struct s_heap	*next;
}	t_heap;

typedef	struct s_env
{
	char			*line;
	char			*var;
	char			*val;
	struct s_env	*next;
}	t_env;


typedef struct	s_shell
{
	t_env	*env;
	// int 	std_in;
	// int 	std_out;
	// int 	std_err;
	t_heap	*heap;
}	t_shell;


/* Garbedge collector! */
void   	*my_malloc(size_t size, t_shell *shell);
void    my_free(t_shell *shell);

/*Libft*/
char	*ft_strdup(const char *s1, t_shell *shell);
char	*ft_strjoin(char const *s1, char const *s2, t_shell *shell);

/* Utils */
char    *ft_strdup_mod(char *str, t_shell *shell);

#endif