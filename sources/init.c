/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 11:46:56 by jwikiera          #+#    #+#             */
/*   Updated: 2022/10/11 13:36:27 by jwikiera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_pipex	*init_pipex(void)
{
	t_pipex	*res;

	res = malloc(sizeof(*res));
	if (!res)
		return (NULL);
	res->is_heredoc = 0;
	res->heredoc_args = NULL;
	res->heredoc_argc = 0;
	res->file1_fd = -1;
	res->file2_fd = -1;
	res->commands = NULL;
	res->commandc = 0;
	return (res);
}

/* pipex->commands is a 2d char array but individual strings are also in argv
 * and should be freed by the OS */
void	free_pipex(t_pipex *pipex)
{
	size_t	i;
	if (pipex && pipex->heredoc_args)
		free(pipex->heredoc_args);
	if (pipex && pipex->commands)
	{
		i = 0;
		while (i < pipex->commandc)
		{
			if (pipex->commands[i])
				ft_free_split(pipex->commands[i], ft_strarrlen(pipex->commands[i]));
			i ++;
		}
		free(pipex->commands);
	}
	if (pipex)
		free(pipex);
}
