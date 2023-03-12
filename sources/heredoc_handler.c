/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 11:12:16 by jwikiera          #+#    #+#             */
/*   Updated: 2022/10/20 11:12:18 by jwikiera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "get_next_line.h"

static int	read_stdin(t_pipex *pipex)
{
	char	*read;

	read = "lol";
	while (read)
	{
		read = get_next_line(STDIN_FILENO);
		if (!read)
			return (pi_error("warning: here-document "
					"delimited by end-of-file", 1));
		if (hrdceq(read, pipex->heredoc_lim))
		{
			free(read);
			return (1);
		}
		if (!ft_append_to_file(pipex->heredoc_fname, read))
		{
			free(read);
			return (pi_error("error: failed to write to buffer file\n", 0));
		}
		free(read);
	}
	return (1);
}

static int	ret(int code, t_pipex *pipex)
{
	unlink(pipex->heredoc_fname);
	return (code);
}

void	child1(t_pipex *pipex, const int p[2])
{
	int	fd;

	fd = open(pipex->heredoc_fname, O_RDONLY);
	if (fd == -1)
		exit(1);
	dup2(fd, STDIN_FILENO);
	dup2(p[1], STDOUT_FILENO);
	close(p[0]);
	close(p[1]);
	execve(pipex->commands[0][0], pipex->commands[0], environ);
	exit(1);
}

void	child2(t_pipex *pipex, const int p[2])
{
	dup2(p[0], STDIN_FILENO);
	dup2(pipex->file1_fd, STDOUT_FILENO);
	close(p[0]);
	close(p[1]);
	execve(pipex->commands[1][0], pipex->commands[1], environ);
	exit(1);
}

int	handle_heredoc(t_pipex *pipex)
{
	int	id;
	int	id2;
	int	p[2];
	int	ret_status;

	if (!read_stdin(pipex))
		return (ret(0, pipex));
	if (pipe(p) == -1)
		return (ret(0, pipex));
	id = fork();
	if (id == -1)
		return (ret(0, pipex));
	if (id == 0)
		child1(pipex, p);
	id2 = fork();
	if (id2 == -1)
		return (ret(0, pipex));
	if (id2 == 0)
		child2(pipex, p);
	close(p[0]);
	close(p[1]);
	ret_status = 0;
	wait(&ret_status);
	//fprintf(stderr, "ret after 1st child: %d\n", ret_status);
	wait(&ret_status);
	//fprintf(stderr, "ret after 2st child: %d\n", ret_status);
	return (ret(ret_status, pipex));
}
