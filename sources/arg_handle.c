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

int	pipe_arg_handle(int argc, char *argv[], t_pipex *pipex)
{
	int	i;

	if (!handle_files(argv[1], argv[argc - 1], pipex))
	{
		ft_putstr_fd("Failed to open files.\n", 2);
		return (0);
	}
	pipex->commands = malloc(sizeof(*pipex->commands) * argc - 3);
	if (!pipex->commands)
	{
		ft_putstr_fd("Failed to malloc pipex->commands.\n", 2);
		return (0);
	}
	i = 2;
	while (i < argc - 1)
	{
		pipex->commands[i - 2] = parse_command(argv[i]);
		if (!pipex->commands[i - 2])
			return (0);
		i ++;
	}
	pipex->commandc = argc - 3;
	return (1);
}

int	arg_handle(int argc, char *argv[], t_pipex *pipex)
{
	if (argc < 5)
	{
		ft_putstr_fd("At least four arguments expected.\n", 2);
		return (0);
	}
	if (!ft_strncmp(argv[1], "here_doc", ft_strlen(argv[1])))
		return (heredoc_arg_handle(argc, argv, pipex));
	return (pipe_arg_handle(argc, argv, pipex));
}
