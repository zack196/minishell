#include "../../includes/parse.h"

char	*generate_file_random()
{
	char	*file;
	int		fd;
	int		fd_urandom;

	fd_urandom = open("/dev/urandom", O_RDONLY, 0777);
	if (fd_urandom == -1)
		return (perror("/dev/urandom"), NULL);
	file = malloc(25 * sizeof (char));
	if (!file)
		return (perror("malloc failed!\n"),close(fd_urandom), NULL);
	file[0] = '/';
	file[1] = 't';
	file[2] = 'm';
	file[3] = 'p';
	file[4] = '/';
	if (read(fd_urandom, file + 5, 19) == -1)
		return (perror("error reading from urandom"), free(file), NULL);
	file[24] = '\0';
	fd = open(file, O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (fd == -1)
		return (free(file),close(fd_urandom), generate_file_random());
	return (close(fd_urandom),close(fd), unlink(file), file);
}

int	nbr_heredoc(t_cmd *cmd)
{
	int		i;
	t_redi	*red;

	i = 0;
	while (cmd)
	{
		red = cmd->in;
		while (red)
		{
			if (red->type == heredoc)
				i++;
			red = red->next;
		}
		cmd = cmd->next;
	}
	return (i);
}

void	fil_in_file(char *file, t_redi *red, t_envi *envi)
{
    int     fd;
    char    *line;
	
    fd = open(file, O_WRONLY | O_CREAT, 0777);
	set_herdoc();
    while (1)
    {
        line = readline(">");
		if(g_heredoc_interrupted == 6)
		{
			close(fd);
			g_heredoc_interrupted = 0;
			fd = open(file, O_WRONLY | O_TRUNC);
            close(fd);
			return;
		}
        if (!line || !ft_strcmp(line, red->file))
            break ;
        line = ft_strjoin(line, "\n");
        if (!line)
            return ;
        if (red->must_exp == 1)
            expand_var(envi, &line);
        write(fd, line, ft_strlen(line));
        free(line);
    }
    free(line);
    close(fd);
}

char	**creat_heredoc(t_cmd *cmd, t_envi *envi)
{
    int     i;
	char	**files;
    t_redi  *red;

	if (nbr_heredoc(cmd) > 16)
		return (ft_putstr_fd("minishell: maximum ", 2)
			, ft_putstr_fd("here-document count exceeded\n", 2), NULL);
	files = malloc(sizeof(char *) * (nbr_heredoc(cmd) + 1));
    if (!files)
        return (NULL);
    i = 0;
	while (cmd)
    {
        red = cmd->in;
        while (red)
        {
            if (red->type == heredoc)
            {
                files[i] = generate_file_random();
                fil_in_file(files[i++], red, envi);
            }
            red = red->next;
        }
        cmd = cmd->next;
    }
    files[i] = NULL;
	return (files);
}
