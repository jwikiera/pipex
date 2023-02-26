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

static int	wait_for_all(size_t proc_amount)
{
	size_t	i;
	int		failed;
	int		status;

	failed = 0;
	i = 0;
	status = 0;
	while (i < proc_amount)
	{
		wait(&status);
		if (status != 0)
			failed = 1;
		i ++;
	}
	return (!failed);
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
		if (!ft_lst_get(pipes, -2))
			return ;
		dup2(((int *)ft_lstlast(pipes)->content)[1], STDOUT_FILENO);
		dup2(((int *)ft_lst_get(pipes, -2)->content)[0], STDIN_FILENO);
	}
	else
	{
		dup2(pipex->file2_fd, STDOUT_FILENO);
		dup2(((int *)ft_lstlast(pipes)->content)[0], STDIN_FILENO);
	}
	close_all_pipes(pipes);
	execve(pipex->commands[i][0], pipex->commands[i], environ);
	exit(1);
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

	i = 0;
	pipes = NULL;
	while (i < pipex->commandc)
	{
		if (pipex->commandc > 0 && i < pipex->commandc - 1)
		{
			if (pipe(p) == -1 || !add_pipe(&pipes, p))
				return (pipe_handler_ret(0, &pipes));
		}
		id = fork();
		if (id == -1)
			return (pipe_handler_ret(0, &pipes));
		if (id == 0)
			handle_child_action(pipex, pipes, i);
		i ++;
	}
	close_all_pipes(pipes);
	return (pipe_handler_ret(wait_for_all(pipex->commandc), &pipes));
}
