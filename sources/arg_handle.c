/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_handle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 11:46:56 by jwikiera          #+#    #+#             */
/*   Updated: 2022/10/11 13:36:27 by jwikiera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	heredoc_arg_handle(int argc, char *argv[], t_pipex *pipex)
{
	pipex->is_heredoc = 1;
	(void) argc;
	(void) argv;
	(void) pipex;
	return (1);
}

static int	check_bins(t_pipex *pipex)
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
			if (!ft_ptstrfd_s("pipex: ", 2))
				return (0);
			if (!ft_ptstrfd_s(pipex->commands[i][0], 2))
				return (0);
			if (!ft_ptstrfd_s(": command not found\n", 2))
				return (0);
			errored = 1;
		}
		i ++;
	}
	return (!errored);
}

static int	pipe_arg_handle(int argc, char *argv[], t_pipex *pipex)
{
	int	i;

	if (!handle_files(argv[1], argv[argc - 1], pipex))
		return (pi_error("failed to open files.\n", 0));
	pipex->commands = malloc(sizeof(*pipex->commands) * argc - 3);
	if (!pipex->commands)
		return (pi_error("failed to malloc pipex->commands.\n", 1));
	i = 2;
	pipex->commandc = 0;
	while (i < argc - 1)
	{
		pipex->commands[i - 2] = parse_command(argv[i]);
		if (!pipex->commands[i - 2])
			return (0);
		i ++;
		pipex->commandc ++;
	}
	return (check_bins(pipex));
}

int	arg_handle(int argc, char *argv[], t_pipex *pipex)
{
	if (argc < 5)
		return (pi_error("At least four arguments expected.\n", 0));
	if (!ft_strncmp(argv[1], "here_doc", ft_strlen(argv[1])))
		return (heredoc_arg_handle(argc, argv, pipex));
	return (pipe_arg_handle(argc, argv, pipex));
}
