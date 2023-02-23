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

void	handle_pipes(t_pipex *pipex)
{
	//int	*fd_reg;

	ft_printf("handling pipes or smth lol (%x)\n", pipex);


	int	id = fork();

	if (id == 0)
	{
		dup2(pipex->file1_fd, 0);
		execve(pipex->commands[0][0], pipex->commands[0], environ);
	}
	waitpid(id, NULL, 0);
}
