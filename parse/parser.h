#ifndef PARSER_H
# define PARSER_H

# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "../minishell.h"

enum
{
	heredoc,
	in,
	out,
	append,
};

typedef struct s_token
{
	int				type;
	char			*content;
	int				expand;
	int				check;
	struct s_token	*next;
}					t_token;

typedef struct s_redi
{
	int				type;
	char			*file;
	int				must_exp;
	struct s_redi	*next;
}					t_redi;

typedef struct s_cmd
{
	char			**cmd;
	int				pipe;
	int				err;
	int				type;
	t_redi			*in;
	t_redi			*out;
	struct s_cmd	*next;
}					t_cmd;
enum
{
	WORD,
	PIPE,
	DOUBLE,
	SINGLE,
	OPERATOR,
	HYPHEN,
	SPACEE,
	SINGLE_EXP,
};

typedef struct s_help 
{ 
	int i; 
	int j; 
	char *prev; 
	char *str; //avant 
	char *str1; //respo
	char *last_str; //apres
	char *join; 
	//char *check_str; 
}					t_help;

int		ft_strchr_2(const char *str, int c);
void	to_exit(void);
int		is_all_spaces(char *str);
int		error_format(t_token *token, t_token *tmp, int i);
int	find_error(t_token *token, t_token *tmp);
int	check_syntax(t_token *token);

void	ft_lstdelone_t(t_token *lst);
t_cmd	*ft_lstlast_cmd(t_cmd *lst);
t_cmd	*ft_lstnew_cmd(void);
void	ft_lstclear_t(t_token **lst);
t_token	*ft_lstlast_m(t_token *lst);
void	ft_lstadd_back_cmd(t_cmd **lst, t_cmd *new);
void	ft_lstadd_back_m(t_token **lst, t_token *new);
t_token	*ft_lstnew_m(char *content);
void	ft_lstadd_back_redi(t_redi **lst, t_redi *new);
t_redi	*ft_lstnew_redi(char *out, int type);
t_redi	*ft_lstlast_redi(t_redi *lst);

void	init_args(t_token *token, t_cmd *cmd);
int	check_redir(t_token *token);
void	set_oper(t_token *token, t_redi **redir, int type);
void	is_operator(t_token *token, t_cmd *cmd);
void	rub_operator(t_cmd *cmd, t_token *token, t_token **tok);
void	init_cmd(t_token **token, t_cmd **cmd);
void	fill_cmd(t_cmd *cmd, t_token *token, int *i);
void	parse_cmd(t_token **token, t_cmd **cmd);

void	ft_remove(t_token *tmp, t_token **curr, t_token **token);
void	remove_spaces(t_token **token, t_token *tok);
int	ft_putendl_fd_2(char *s, char *str, int fd);

int	whish_separator(char *line);
int	type_token(char *content);
int	take_separator(char *line, t_token **token);
int	with_quotes(char *line, t_token **token, int c, int *flag);
int	take_word(char *line, t_token **token, int *flag);
int	token_line(char *line, t_token **token);

char	**ft_split(char const *s, char c);
void	ft_free(char **str);

void    get_input(t_cmd *command);
void	check_cmd(t_cmd *cmd);
void	ft_minishell(t_env **env, t_token **token, t_cmd **cmd);

void	ft_lstclear_2(t_redi **lst);
void	set_cmd(t_cmd *cmd);
void	ft_free_tab2(char **arr);
void	clear_cmds(t_cmd **cmd);

/*EXpand*/
void	handler_expand(t_token **token, t_env *env, t_token *tok);
void	check_exp(t_token *tok, t_env *env);
void	hyphen_exp(t_token *tok, t_env *env);
char	*get_value_of_exp(t_env *env, char *key);
void	trim_quotes(t_token *token);
int		join_str(t_token **token, t_token *tmp);

void	expand_var(t_env *env, char **content);
int	    count(char *str);
void	ft_free_2(char *str1, char *str2, char *str3);
int		exp_here(int curr, int next);
int		must_expand(int next);
void	check_tokens(t_token *token);
#endif
