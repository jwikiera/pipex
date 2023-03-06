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
	//fprintf(fopen("/Users/jwikiera/Projets/pipex/arglog.txt", "a"), "---------\n");
	while (i < argc - 1)
	{
		///////pipex->commands[i - 2] = parse_command(argv[i]);
		pipex->commands[i - 2] = ft_quotesplit2(argv[i]);
		fprintf(stderr, "argv[%d]: %s\n", i, argv[i]);
		//fprintf(fopen("/Users/jwikiera/Projets/pipex/arglog.txt", "a"), "argv[%d]: %s\n", i, argv[i]);
		//fprintf(stderr, "argv[%d]: %s\n", i, argv[i]);
		//fprintf(stdout, "strarr of parsed (len of array is %zu): \n", ft_strarrlen(pipex->commands[i - 2]));
		//ft_println_strarr(pipex->commands[i - 2], 0, 1);
		if (!pipex->commands[i - 2])
			return (0);
		i ++;
		pipex->commandc ++;
	}
	//exit(69);
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
