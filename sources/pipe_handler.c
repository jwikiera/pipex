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

/*static int	recurs_pipe(t_pipex *pipex, size_t cnt)
{
	int	p[2];
	int	id;
	int	id2;
	int	wait_ret;

	wait_ret = 0;

	id = fork();
	ft_printf("hello from id %d (cnt: %d)\n", id, cnt);
	if (id < 0)
		return (-1);
	if (id == 0)
	{
		pipe(p);
		id2 = fork();
		ft_printf("hello from id2 %d (cnt: %d)\n", id2, cnt);
		if (id2 == 0)
		{
			ft_printf("execing cnt: %d\n", cnt);

			if (cnt == 0)
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
			execve(pipex->commands[cnt][0], pipex->commands[cnt], environ);
		}
		else
		{
			close(p[0]);
			close(p[1]);
			ft_printf("waiting for pid2 %d, cnt %\n", id2, cnt);
			waitpid(id2, &wait_ret, 0);
			if (cnt == pipex->commandc)
				return (wait_ret);
			else {
				cnt ++;
				recurs_pipe(pipex, cnt);
			}
		}
		close(p[0]);
		close(p[1]);
	}
	else
	{
		ft_printf("waiting for pid %d, cnt %\n", id, cnt);
		waitpid(id, &wait_ret, 0);
	}
	return (wait_ret);
}*/

int	iter_pipe(t_pipex *pipex)
{
	size_t	i;
	int		id;
	int		p[2];
	t_list	*pipes;
	t_list	*pchild;

	i = 0;
	pipes = NULL;
	ft_printf("hello from parent %d\n", getpid());

	/*if (fork() == 0)
	{
		dup2(pipex->file1_fd, STDIN_FILENO);
		execve(pipex->commands[1][0], pipex->commands[1], environ);
	}*/

	//return (1);
	while (i < pipex->commandc)
	{
		if (pipex->commandc > 0 && i < pipex->commandc - 1)
			//ft_putstr_fd("bruh\n", 1);
		{
			if (pipe(p) == -1)
				return (-1);
			//printf("1. wrote: %zd bytes to %d\n", write(p[1], "test\n", 5), p[1]);
			pchild = ft_lstnew(malloc(sizeof(int) * 2));
			((int *)pchild->content)[0] = p[0];
			((int *)pchild->content)[1] = p[1];
			p[0] = 0;
			p[1] = 0;
			ft_lstadd_back(&pipes, pchild);
			//printf("2. wrote: %zd bytes to %d\n", write(((int *) ft_lstlast(pipes)->content)[1], "test\n", 5), ((int *) pipes->content)[1]);
		}

		fprintf(stderr, "i: %zu, there are following pipes:\n", i);
		for (int j = 0; j < ft_lstsize(pipes); ++j) {
			fprintf(stderr, "pipe n°%d, [0]: %d, [1]: %d\n", j, ((int *)ft_lst_get(pipes, j)->content)[0], ((int *)ft_lst_get(pipes, j)->content)[1]);
		}

		id = fork();
		if (id == -1)
			return (-1);
		if (id == 0)
		{
			fprintf(stderr, "hello from child %zu, we will be executing <%s>, lstsize: %d\n", i, pipex->commands[i][0],
				   ft_lstsize(pipes));
			if (i == 0)
			{
				/* connect file1 to current input */
				dup2(pipex->file1_fd, STDIN_FILENO);

				/* connect output to last pipe write */
				fprintf(stderr, "(i %zu) connecting output to last pipe[1] (%d)\n", i, ((int *)ft_lstlast(pipes)->content)[1]);
				dup2(((int *)ft_lstlast(pipes)->content)[1], STDOUT_FILENO);
				//printf("wrote: %zd bytes to last pipe\n", write(((int *)ft_lstlast(pipes)->content)[1], "test\n", 5));

				//close(((int *)ft_lstlast(pipes)->content)[0]);

				close(((int *)ft_lstlast(pipes)->content)[1]);
			}
			else if (i < pipex->commandc - 1)
			{
				/* connect current pipe input to this output */
				fprintf(stderr, "(i %zu) connecting last pipe[1] (%d) to 1\n", i, ((int *)ft_lstlast(pipes)->content)[1]);
				dup2(((int *)ft_lstlast(pipes)->content)[1], STDOUT_FILENO);

				/* connecting one before last pipe output to this input */
				fprintf(stderr, "(i %zu) connecting before last pipe[0] (%d) to 0\n", i, ((int *)ft_lst_get(pipes, -2)->content)[0]);
				dup2(((int *)ft_lst_get(pipes, -2)->content)[0], STDIN_FILENO);
			}
			else
			{
				//closing

				//connect input of previous pipe to this input
				fprintf(stderr, "(i %zu) connecting last pipe[0] (%d) to input\n", i, ((int *)ft_lstlast(pipes)->content)[0]);
				dup2(((int *)ft_lstlast(pipes)->content)[0], STDIN_FILENO);

				/* we must close the read of the last pipe */
				close(((int *) ft_lstlast(pipes)->content)[0]);
			}
			//close(((int *) ft_lstlast(pipes)->content)[0]);
			//close(((int *) ft_lstlast(pipes)->content)[1]);

			for (int j = 0; j < ft_lstsize(pipes); ++j) {
				//fprintf(stderr, "pipe n°%d, [0]: %d, [1]: %d\n", j, ((int *)ft_lst_get(pipes, j)->content)[0], ((int *)ft_lst_get(pipes, j)->content)[1]);
				close(((int *)ft_lst_get(pipes, j)->content)[0]);
				close(((int *)ft_lst_get(pipes, j)->content)[1]);
			}

			if (ft_strarrlen(pipex->commands[i]) == 2)
				fprintf(stderr, "executing command %s %s...\n", pipex->commands[i][0], pipex->commands[i][1]);
			else
				fprintf(stderr, "executing command %s %s %s...\n", pipex->commands[i][0], pipex->commands[i][1], pipex->commands[i][2]);

			if (i == 2)
			{
				ft_putstr_fd("hello from cut!\n", 2);
			}
			//ft_println_strarr(pipex->commands[i], 0, 1);
			execve(pipex->commands[i][0], pipex->commands[i], environ);
			exit(1);
		}
		//fprintf(stderr, ("closing last pipe (out of %d) in main\n", ft_lstsize(pipes));
		//close(((int *) ft_lstlast(pipes)->content)[0]);
		//close(((int *) ft_lstlast(pipes)->content)[1]);
		fprintf(stderr, "incrementing i (from %zu to %zu)\n", i, i + 1);
		i ++;
	}
	printf("closing pipes in main (%d pipes)\n", ft_lstsize(pipes));
	t_list *iter = pipes;
	int j = 0;
	while (iter)
	{
		fprintf(stderr, "closing ends %d and %d\n", ((int *) iter->content)[0], ((int *) iter->content)[1]);
		close(((int *) iter->content)[0]);
		close(((int *) iter->content)[1]);
		iter = iter->next;
		j ++;
	}
	printf("got here\n");
	for(size_t j=0;j<pipex->commandc;j++) // loop will run n times (n=5)
		wait(NULL);
	printf("got here2\n");

	iter = pipes;
	j = 0;
	while (iter)
	{
		ft_printf("pipe %d: %d, %d\n", j, ((int *) iter)[0], ((int *) iter)[1]);
		iter = iter->next;
		j ++;
	}

	ft_lstclear(&pipes, ft_delnode);
	return (0);
}

/* We write into p[1] and read from p[0] */
int	handle_pipes(t_pipex *pipex)
{
	ft_printf("handling pipes or smth lol (%x)\n", &pipex);

	int iter = 1;

	//recurs_pipe(pipex, cnt);

	if (iter)
	{
		iter_pipe(pipex);
	}
	else
	{
		int p[2];
		if (pipe(p) < 0)
			return (0);

		int id = fork();

		if (id == -1)
			return (0);

		if (id == 0)
		{
			fprintf(stderr, "hello from first child, we're executing %s on pid %d\n", pipex->commands[0][0], getpid());
			dup2(pipex->file1_fd, 0);

			dup2(p[1], STDOUT_FILENO);
			close(p[1]);
			//close(p[0]);

			execve(pipex->commands[0][0], pipex->commands[0], environ);
		}
		else
		{
			int id2 = fork();
			if (id2 == 0)
			{
				fprintf(stderr, "hello from second child, we're executing %s on pid %d\n", pipex->commands[1][0], getpid());
				dup2(p[0], STDIN_FILENO);
				//close(p[0]);
				close(p[1]);
				execve(pipex->commands[1][0], pipex->commands[1], environ);
			}
			else
			{
				//close(p[0]);
				close(p[1]);
				waitpid(id, NULL, 0);
				waitpid(id2, NULL, 0);
			}
		}
	}



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
