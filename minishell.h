#ifndef MINISHELL_H
#define MINISHELL_H

# include <stdio.h>
# include <unistd.h> 
# include <stdlib.h>
# include <limits.h>
# include <fcntl.h>
# include "readline/history.h"
# include "readline/readline.h"
# include "libft/libft.h"
# include <sys/wait.h>

typedef struct s_cmd	t_cmd;
typedef struct s_redi	t_redi;


typedef	struct	s_heap
{
	void			*ptr;
	struct	s_heap	*next;
}	t_heap;

// void    error(char *msg_err);


// /*BUILD_IN*/
// void	cd(const char *path, t_env **sh_env);
// void	export(t_env **envi, char *line);
// void	_export(t_env *env);
// void	print_env(t_env *env, int mode_export);
// void    pwd(void);
// void    env_exit(char *exit_num);
// void	echo(char **argv, int flag_n);
// void    unset(t_env **env, char *var);
// void	exec_build_in(t_env **sh_env, char **cmd, int *bool_build_in);

// /*EXEC*/

// void	proc(int fd_in, int fd_out, t_env **sh_env, char **cmd);
// void	execution(t_env **sh_env, t_cmd *cmd);
// void	handel_red(t_cmd *cmd, int *fd_in, int *fd_out);
#endif