#ifndef MINISHELL_H
#define MINISHELL_H

# include <stdio.h>
# include <unistd.h> 
# include <stdlib.h>
# include <limits.h>
# include <fcntl.h>
# include "libft/libft.h"
# include <sys/wait.h>

typedef struct s_cmd	t_cmd;
typedef struct s_redi	t_redi;
typedef struct s_env
{
	char			*line;
	char			*var;
	char			*val;
	struct s_env	*next;
}	t_env;


typedef	struct	s_heap
{
	void			*ptr;
	struct	s_heap	*next;
}	t_heap;

void	*my_malloc(size_t size, int mode_free);
void    error(char *msg_err);

/*Env*/
char	*get_var_env(char *line);
char	*get_val_env(char *line);
void	init_env(t_env **shell_env, char **env);
void	add_env(t_env **env, t_env *new);
t_env	*new_element_env(char *line);

/*BUILD_IN*/
void	cd(const char *path, t_env **sh_env);
void	export(t_env **envi, char *line);
void	_export(t_env *env);
void	print_env(t_env *env, int mode_export);
void    pwd(void);
void    env_exit(char *exit_num);
void	echo(char **argv, int flag_n);
void    unset(t_env **env, char *var);
void	exec_build_in(t_env **sh_env, char **cmd, int *bool_build_in);

/*Libft*/
int		ft_atoi(const char *str);
int		ft_isalnum(int c);
int		ft_isdigit(int c);
int		ft_isalpha(int c);
size_t	ft_strlen(const char *str);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strdup(const char *s1);
int 	ft_strcmp(char *s1, char *s2);
char	*ft_strrchr(const char *s, int c);
int 	ft_strncmp(char *s1, char *s2, int n);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	**ft_split(char const *s, char c);

/*EXEC*/

void	proc(int fd_in, int fd_out, t_env **sh_env, char **cmd);
void	execution(t_env **sh_env, t_cmd *cmd);
void	handel_red(t_cmd *cmd, int *fd_in, int *fd_out);
#endif