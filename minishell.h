#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

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
	t_heap	*heap;
}	t_shell;


/* Garbage_collector.c */
void   	*my_malloc(size_t size, t_shell *shell);
void    my_free(t_shell *shell);

/*Libft*/
char	*ft_strdup(const char *s1, t_shell *shell);
char	*ft_strjoin(char const *s1, char const *s2, t_shell *shell);
char	*ft_strchr(const char *s, int c);
int		ft_strcmp(const char *str1, const char *str2);
size_t	ft_strlen(const char *str);
void	ft_putstr(char *str);

/* Utils */
char    *ft_strdup_mod(char *str, t_shell *shell);
void    error_msg(char *err_msg);


/* Envirenement */
void	init_env(t_shell *shell, char **env);

/* Built in */
void	export(char *line, t_shell *shell);
void	unset(t_shell *shell, char *var);
void	environment(t_shell *shell);
void	pwd();
void	echo(char **argv, int ac);

#endif