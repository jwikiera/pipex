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
#include <sys/wait.h>

static void	close_all_pipes(t_list *lst)
{
	t_list	*iter;
	int		i;

	iter = lst;
	i = 0;
	while (iter)
	{
		close(((int *) iter->content)[0]);
		close(((int *) iter->content)[1]);
		iter = iter->next;
		i ++;
	}
}

static int	wait_for_all(t_list *ids)
{
	t_list	*iter;
	int		status;

	status = 0;
	iter = ids;
	while (iter)
	{
		waitpid(*((int *)iter->content), &status, 0);
		if (status != 0)
			status = WEXITSTATUS(status);
		iter = iter->next;
	}
	return (status);
}

static void	handle_child_action(t_pipex *pipex, t_list *pipes, size_t i)
{
	if (!ft_lstlast(pipes))
		return ;
	if (i == 0)
	{
		dup2(pipex->file1_fd, STDIN_FILENO);
		dup2(((int *)ft_lstlast(pipes)->content)[1], STDOUT_FILENO);
	}
	else if (i < pipex->commandc - 1)
	{
		//close(pipex->file1_fd);
		//close(pipex->file2_fd);
		if (!ft_lst_get(pipes, -2))
			return ;
		dup2(((int *)ft_lstlast(pipes)->content)[1], STDOUT_FILENO);
		dup2(((int *)ft_lst_get(pipes, -2)->content)[0], STDIN_FILENO);
	}
	else
	{
		//close(pipex->file1_fd);
		dup2(pipex->file2_fd, STDOUT_FILENO);
		dup2(((int *)ft_lstlast(pipes)->content)[0], STDIN_FILENO);
	}
	close_all_pipes(pipes);
	if (ft_command_ex(pipex->commands[i][0], environ) &&  (i != 0 || (pipex->file1_fd != -1)))
	{
		//fprintf(stderr, "executing %s with pid %d\n", pipex->commands[i][0], getpid());
		execve(pipex->commands[i][0], pipex->commands[i], environ);
	}
	exit(127);
}

static int	add_pipe(t_list **lst, const int p[2])
{
	t_list	*pchild;
	void	*content;

	content = malloc(sizeof(int) * 2);
	if (!content)
	{
		return (0);
	}
	pchild = ft_lstnew(content);
	if (!pchild)
	{
		return (0);
	}
	((int *)pchild->content)[0] = p[0];
	((int *)pchild->content)[1] = p[1];
	ft_lstadd_back(lst, pchild);
	return (1);
}

/* We write into p[1] and read from p[0] */
int	handle_pipes(t_pipex *pipex)
{
	size_t	i;
	int		id;
	int		p[2];
	t_list	*pipes;
	t_list	*ids;

	i = 0;
	pipes = NULL;
	ids = NULL;
	while (i < pipex->commandc)
	{
		if (pipex->commandc > 0 && i < pipex->commandc - 1
			&& (pipe(p) == -1 || !add_pipe(&pipes, p)))
			return (pipe_handler_ret(0, &pipes, &ids));
		id = fork();
		if (id == -1)
			return (pipe_handler_ret(0, &pipes, &ids));
		if (id == 0)
			handle_child_action(pipex, pipes, i);
		if (!ft_lstadd_int(id, &ids))
			return (pipe_handler_ret(0, &pipes, &ids));
		i ++;
	}
	close_all_pipes(pipes);
	return (pipe_handler_ret(wait_for_all(ids), &pipes, &ids));
}
