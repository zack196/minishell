#ifndef MINISHELL_H
#define MINISHELL_H

# include <stdio.h>
# include <unistd.h> 
# include <stdlib.h>

typedef struct s_env
{
	char			*line;
	char			*var;
	char			*val;
	struct s_env	*next;
}	t_env;

typedef struct s_minishell
{
	t_env	*env;
}	t_minishell;

typedef	struct	s_heap
{
	void			*ptr;
	struct	s_heap	*next;
}	t_heap;

void	*my_malloc(size_t size, int mode_free);


/*Env*/
char	*get_var(char *line);
char	*get_val(char *line, int *append);
void	init_env(t_env **shell_env, char **env);
void	add_env(t_env **env, t_env *new);
t_env	*new_element_env(char *line);

/*BUILD_IN*/
void    export(t_minishell *sh, char *line);
void    unset(t_minishell *sh, char *var);
void	print_env(t_env *env, int mode_export);
void    _env(t_minishell *sh);
void	_export(t_minishell *sh);

/*Libft*/
int		ft_isalnum(int c);
int		ft_isalpha(int c);
size_t	ft_strlen(const char *str);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strdup(const char *s1);
int ft_strcmp(char *s1, char *s2);
char	*ft_strrchr(const char *s, int c);
int ft_strncmp(char *s1, char *s2, int n);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	**ft_split(char const *s, char c);
#endif