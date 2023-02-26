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

/* file 1 is repurposed as the file to append to */
/* file2 is repurposed as the heredoc buffer */
static int	heredoc_arg_handle(int argc, char *argv[], t_pipex *pipex)
{
	if (argc < 6)
		return (pi_error("at least five arguments expected.\n", 0));
	if (!handle_files_heredoc(argv[5], pipex))
		return (0);
	pipex->is_heredoc = 1;
	pipex->heredoc_lim = argv[2];
	pipex->commandc = 2;
	pipex->commands = malloc(sizeof(*pipex->commands) * 2);
	if (!pipex->commands)
		return (0);
	pipex->commands[0] = parse_command(argv[3]);
	pipex->commands[1] = parse_command(argv[4]);
	if (!pipex->commands[0] || !pipex->commands[1])
		return (0);
	if (!handle_bins(pipex))
		return (0);
	return (1);
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
	return (handle_bins(pipex));
}

int	arg_handle(int argc, char *argv[], t_pipex *pipex)
{
	if (argc < 5)
		return (pi_error("at least four arguments expected.\n", 0));
	if (!ft_strncmp(argv[1], "here_doc", ft_strlen(argv[1])))
		return (heredoc_arg_handle(argc, argv, pipex));
	return (pipe_arg_handle(argc, argv, pipex));
}
