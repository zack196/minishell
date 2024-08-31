#include "../../includes/parse.h"

int	get_idx_of(char *str, int c)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (0);
}
void	*fct(t_envi **envi)
{
	char	*pwd;
	char	buff[PATH_MAX];

	pwd = getcwd(buff, PATH_MAX);
	if (!pwd)
	{
		// perror("");
		return NULL;
	}
	ft_lstadd_back_env(envi, ft_lstnew_env(ft_strdup("PWD"), ft_strdup(pwd), 1));
	ft_lstadd_back_env(envi, ft_lstnew_env(ft_strdup("SHLVL"), ft_strdup("1"), 1));
	ft_lstadd_back_env(envi,
		ft_lstnew_env(ft_strdup("PATH"), ft_strdup("/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:."), 1));
		//TODO ta thandli hadi ta hiya path khaso ykon
	return (envi);
}
void	*parse_env(char **env, t_envi **dup_env)
{
	int	i;

	i = 0;
	if (!env)
		return (NULL);
	ft_lstadd_back_env(dup_env, ft_lstnew_env(ft_strdup("OLDPWD"), NULL, 0));
	ft_lstadd_back_env(dup_env, ft_lstnew_env(ft_strdup("?"), NULL, 0));
	if (!*env)
		return (fct(dup_env));
	while (*env)
	{
		i = get_idx_of(*env, '=');
		ft_lstadd_back_env(dup_env,
			ft_lstnew_env(ft_substr(*env, 0, i),
				ft_substr(*env, i + 1, ft_strlen(*env) - i), 0));
		env++;
	}
	return (dup_env);
}
