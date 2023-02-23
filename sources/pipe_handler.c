/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 11:12:16 by jwikiera          #+#    #+#             */
/*   Updated: 2022/10/20 11:12:18 by jwikiera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	recurs_pipe(t_pipex *pipex, size_t *cnt)
{
	int	p[2];
	int	id;
	int	id2;
	int	wait_ret;

	wait_ret = 0;
	id = fork();
	if (id < 0)
		return (-1);
	if (id == 0)
	{
		id2 = fork();
		if (id2 == 0)
		{
			ft_printf("execing cnt: %d\n", *cnt);
			pipe(p);
			if (*cnt == 0)
			{
				dup2(pipex->file1_fd, 0);

			}
			else
			{
				dup2(p[0], 0);
			}
			dup2(p[1], 1);
			close(p[0]);
			close(p[1]);
			execve(pipex->commands[*cnt][0], pipex->commands[*cnt], environ);
		}
		else
		{
			close(p[0]);
			close(p[1]);
			waitpid(id2, &wait_ret, 0);
			if (*cnt == pipex->commandc)
				return (wait_ret);
			else {
				(*cnt)++;
				recurs_pipe(pipex, cnt);
			}
		}
		close(p[0]);
		close(p[1]);
	}
	else
	{
		waitpid(id, &wait_ret, 0);
	}
	return (wait_ret);
}

/* We write into p[1] and read from p[0] */
int	handle_pipes(t_pipex *pipex)
{
	size_t	cnt;
	ft_printf("handling pipes or smth lol (%x)\n", pipex);

	cnt = 0;
	recurs_pipe(pipex, &cnt);
	/*int	id = fork();
	if (id < 0)
		return (0);
	if (id == 0)
	{
		int p[2];
		if (pipe(p) < 0)
			return (0);

		ft_printf("hello from child\n");
		dup2(pipex->file1_fd, 0);

		int id2 = fork();
		if (id2 < 0)
			return (0);
		if (id2 == 0)
		{
			ft_printf("hello from child's child, we are executing %s\n", pipex->commands[1][0]);
			dup2(p[0], 0);
			close(p[0]);
			close(p[1]);
			dup2(pipex->file2_fd, 1);
			execve(pipex->commands[1][0], pipex->commands[1], environ);
		}
		else
		{
			int	id3 = fork();
			if (id3 < 0)
				return (0);
			if (id3 == 0)
			{
				ft_printf("hello from child's child's child, we're executing %s\n", pipex->commands[0][0]);
				dup2(p[1], 1);
				close(p[0]);
				close(p[1]);
				execve(pipex->commands[0][0], pipex->commands[0], environ);
			}
			else
			{
				close(p[0]);
				close(p[1]);
				waitpid(id3, NULL, 0);
			}
			waitpid(id2, NULL, 0);
		}
	}
	else
	{
		waitpid(id, NULL, 0);
	}
	 */
	return (1);
}
