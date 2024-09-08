/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handel_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-oirg <zel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 21:53:07 by zel-oirg          #+#    #+#             */
/*   Updated: 2024/09/08 12:56:34 by zel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parse.h"

char	*generate_file_random(void)
{
	char	*file;
	int		fd;
	int		fd_urandom;

	fd_urandom = open("/dev/urandom", O_RDONLY, 0777);
	if (fd_urandom == -1)
		return (perror("/dev/urandom"), NULL);
	file = malloc(25 * sizeof (char));
	if (!file)
		return (perror("malloc failed!\n"), close(fd_urandom), NULL);
	(SIGEV_SIGNAL) && (file[0] = '/', file[1] = 't', file[2] = 'm');
	(SIGEV_SIGNAL) && (file[3] = 'p', file[4] = '/');
	if (read(fd_urandom, file + 5, 19) == -1)
		return (perror("error reading from urandom"), free(file), NULL);
	file[24] = '\0';
	fd = open(file, O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (fd == -1)
		return (free(file), close(fd_urandom), generate_file_random());
	return (close(fd_urandom), close(fd), unlink(file), file);
}

char	*fill_in_content(char *line, char *new_del, char *content)
{
	char	*res;

	line = ft_strjoin(line, "\n");
	res = ft_strjoin(content, line);
	if (!line || !res)
		return (free(line), free(content), free(new_del), NULL);
	free(line);
	return (res);
}

char	*fill_file(char *del, t_redi *red, t_envi *envi)
{
	char	*content;
	char	*line;
	char	*new_del;

	content = ft_strdup("");
	new_del = remove_quot(del);
	while (1)
	{
		set_herdoc();
		line = readline(">");
		if (g_heredoc_interrupted == 6)
		{
			g_heredoc_interrupted = 0;
			set_exit_status(1, &envi);
			free(content);
			content = NULL;
			break ;
		}
		if (!line || !ft_strcmp(line, new_del))
			break ;
		if (red->must_exp == 1)
			expand_var(envi, &line);
		content = fill_in_content(line, new_del, content);
	}
	return (free(line), free(new_del), content);
}

int	here_doc_op(t_redi *red, t_envi *envi, t_cmd *ptr)
{
	char	*file_content;
	char	*file_name;
	int		fd;

	file_content = fill_file(red->file, red, envi);
	if (!file_content)
		return (0);
	file_name = generate_file_random();
	fd = open(file_name, O_WRONLY | O_CREAT, 0777);
	if (fd == -1)
		exit(1);
	write(fd, file_content, ft_strlen(file_content));
	free(file_content);
	close(fd);
	if (is_last_in(red))
	{
		fd = open(file_name, O_RDONLY, 0777);
		ptr->fd_hdoc = fd;
	}
	unlink(file_name);
	free(file_name);
	return (1);
}

int	here_doc(t_cmd **cmd, t_envi *envi)
{
	t_cmd	*ptr;
	t_redi	*red;
	int		i;

	ptr = *cmd;
	while (ptr)
	{
		red = ptr->red;
		while (red)
		{
			if (red->type == heredoc)
			{
				i = here_doc_op(red, envi, ptr);
				if (i == 0)
					return (0);
			}
			red = red->next;
		}
		ptr = ptr->next;
	}
	return (1);
}
