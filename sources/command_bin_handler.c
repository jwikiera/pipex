/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_bin_handler.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 11:46:56 by jwikiera          #+#    #+#             */
/*   Updated: 2022/10/11 13:36:27 by jwikiera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	printf_cmn_ntfnd(char *command)
{
	if (!ft_ptstrfd_s("pipex: ", 2))
		return (0);
	if (!ft_ptstrfd_s(command, 2))
		return (0);
	if (!ft_ptstrfd_s(": command not found\n", 2))
		return (0);
	return (1);
}

int	transform_bin(size_t i, t_pipex *pipex)
{
	char	*bak;

	bak = ft_strdup(pipex->commands[i][0]);
	if (!bak)
		return (0);
	free(pipex->commands[i][0]);
	pipex->commands[i][0] = NULL;
	pipex->commands[i][0] = ft_getpath_current(bak, environ);
	free(bak);
	if (!pipex->commands[i][0])
		return (0);
	return (1);
}

/* printf_cmn_ntfnd: command not found is not fatal apparently */
int	handle_bins(t_pipex *pipex)
{
	size_t	i;
	int		errored;

	i = 0;
	errored = 0;
	while (i < pipex->commandc)
	{
		if (ft_strarrlen(pipex->commands[i]) < 1)
		{
			errored = 1;
			pi_error("command is empty", 0);
		}
		else if (!ft_command_ex_current(pipex->commands[i][0], environ))
		{
			if (!printf_cmn_ntfnd(pipex->commands[i][0]))
				return (1);
			errored = 0;
		}
		else if (!transform_bin(i, pipex))
			return (0);
		i ++;
	}
	return (!errored);
}
