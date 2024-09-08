/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-oirg <zel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 21:19:39 by namrene           #+#    #+#             */
/*   Updated: 2024/09/08 13:07:45 by zel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "../libft/libft.h"
# include <dirent.h>
# include <fcntl.h>
# include <limits.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <term.h>
# include <unistd.h>
# include <curses.h>
# include <signal.h>
# include <sys/ioctl.h>
# include <stdio.h>
# include <term.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>
# include <stdlib.h>
# include <unistd.h>

int	g_heredoc_interrupted;

enum
{
	heredoc,
	in,
	out,
	append,
};

typedef struct s_help
{
	int				i;
	int				j;
	char			*prev;
	char			*str;
	char			*str1;
	char			*last_str;
	char			*join;
	char			*check_str;
	int				dollar_count;
}					t_help;

typedef struct s_redi
{
	int				type;
	char			*file;
	int				fd_heredoc;
	int				must_exp;
	struct s_redi	*next;
}					t_redi;

typedef struct s_token
{
	int				type;
	char			*content;
	int				expand;
	int				next_starts_with_quote;
	int				check;
	struct s_token	*next;
}					t_token;

typedef struct s_envi
{
	char			*key;
	char			*value;
	int				is_min;
	int				empty_once;
	struct s_envi	*next;
}					t_envi;

typedef struct s_cmd
{
	char			**cmd;
	int				pipe;
	int				err;
	int				type;
	pid_t			pid;
	int				fd_hdoc;
	t_redi			*red;
	struct s_cmd	*next;
}					t_cmd;

enum
{
	WORD,
	PIPE,
	DOUBLE,
	SINGLE,
	OPR,
	HYPHEN,
	SPACEE,
	SINGLE_EXP,
};

int		is_all_spaces(char *str);
int		token_line(char *line, t_token **token, int i);
int		take_separator(char *line, t_token **token);
int		whish_separator(char *line);
void	check_args(int ac, char **av, t_envi **dup_env, char **env);
int		with_quotes(char *line, t_token **token, int c, int *flag);
int		take_word(char *line, t_token **token, int *flag);
int		type_token(char *content);
t_token	*ft_lstnew_m(char *content);
t_token	*ft_lstlast_m(t_token *lst);
void	ft_lstadd_back_m(t_token **lst, t_token *new);
void	ft_lstdelone_t(t_token *lst);
void	ft_lstclear_t(t_token **lst);
t_envi	*ft_lstnew_env(char *key, char *value, int val);
t_envi	*ft_lstlast_env(t_envi *lst);
void	ft_lstadd_back_env(t_envi **lst, t_envi *new);
void	ft_lstclear(t_token **lst);
void	ft_lstdelone(t_token *lst);
t_cmd	*ft_lstnew_cmd(void);
t_cmd	*ft_lstlast_cmd(t_cmd *lst);
void	ft_lstadd_back_cmd(t_cmd **lst, t_cmd *new);
void	clear_cmds(t_cmd **cmd);
int		ft_strchr_2(const char *str, int c);
void	ft_lstadd_back_redi(t_redi **lst, t_redi *new);
t_redi	*ft_lstnew_redi(char *out, int type);
t_redi	*ft_lstlast_redi(t_redi *lst);
void	ft_lstclear_2(t_redi **lst);
void	ft_free_env(t_envi **envi);
void	*parse_env(char **env, t_envi **dup_env);
int		get_idx_of(char *str, int c);
void	ft_minishell(t_envi **env, t_token **token, t_cmd **cmd);
void	handler_expand(t_token **token, t_envi *env, t_token *tok);
void	trim_quotes(t_token *token);
void	check_exp(t_token *tok, t_envi *env);
void	hyphen_exp(t_token *tok, t_envi *env);
char	*get_value_of_exp(t_envi *env, char *key);
int		must_expand(int next);
int		exp_here(int curr, int next);
int		count(char *str);
void	expand_var(t_envi *env, char **content);
void	here_doc_exp(t_token *token);
int		join_str(t_token **token, t_token *tmp);
void	ft_free(char **str);
void	set_type(t_token *tok);
void	ft_free_2(char *str1, char *str2, char *str3);
void	ft_free_tab2(char **arr);
void	remove_spaces(t_token **token, t_token *tok);
void	ft_remove(t_token *tmp, t_token **curr, t_token **token);
int		check_syntax(t_token *token, t_token *tmp);
int		ft_ptndl(char *s, char *str, int fd);
int		find_error(t_token *token, t_token *tmp);
int		error_format(t_token *token, t_token *tmp, int i);
void	parse_cmd(t_token **token, t_cmd **cmd, t_envi **env);
void	init_cmd(t_token **token, t_cmd **cmd, t_envi **env);
void	rub_operator(t_cmd *cmd, t_token *token, t_token **tok, t_envi **env);
void	is_operator(t_token *token, t_cmd *cmd, t_envi **env);
int		check_redir(t_token *token, t_envi **env);
void	set_oper(t_token *token, t_redi **redir, int type);
void	set_cmd(t_cmd *cmd);
void	init_args(t_token *token, t_cmd *cmd);
void	fill_cmd(t_cmd *cmd, t_token *token, int *i);
char	*remove_quot(char *str);
int		count_consecutive_dollars(char *str);
void	exe_cmd(char **cmd, t_envi *envi, int fd_in, int fd_out);
int		here_doc(t_cmd **cmd, t_envi *envi);
void	clean_heredoc(char **heredoc);
void	_exec(t_cmd *cmd, t_envi **envi);
void	piping(t_cmd *cmd, int fd, t_envi **envi);
int		is_build(char **cmd);
int		nbr_heredoc(t_cmd *cmd);
void	build_in_exe(t_cmd *cmd, t_envi **env);
int		build_in(char **cmd, t_envi **env);
char	**creat_heredoc(t_cmd *cmd, t_envi *envi);
int		_echo(char **av, t_envi **envi);
int		unset(char **av, t_envi **envi);
int		env(t_envi *envi);
int		handel_red(t_cmd *cmd, int *fd_in, int *fd_out);
int		export(char **av, t_envi **envi);
int		pwd(t_envi *envi);
int		_exit_(char **av, t_envi **envi);
int		cd(char *path, t_envi **envi);
int		check_var(char *var, char *fct, t_envi **envi);
char	**split_space(char **ptr);
t_envi	*find_node(t_envi *envi, char *key);
char	**exec_expand(char **cmd);
char	**remove_empty_string(char **ptr);
void	set_exit_status(int status, t_envi **envi);
void	set_default(void);
void	set_herdoc(void);
void	sig_int_handler(int s);
void	close_hdoc(t_cmd *cmd);
void	error_cmd(char *cmd, char *err_msg, int n);
int		_export(char *line, t_envi **envi);
int		count_env(t_envi *envi);
void	sh_level(t_envi *envi);
char	**get_env(t_envi *envi);
char	*get_path_cmd(char *cmd, char **env);
void	print_export(t_envi *cpy);
t_envi	*cpy_env(t_envi *envi);
void	export_node(t_envi **envi, char *key, char *value, int append);
int		is_last_in(t_redi *red);
int		sp_cmp(char *str);
void	sig(void);
#endif