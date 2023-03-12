/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 11:12:16 by jwikiera          #+#    #+#             */
/*   Updated: 2022/10/20 11:12:18 by jwikiera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <errno.h>

void	handle_exit(char *msg, int code, t_pipex *pipex)
{
	if (pipex)
		free_pipex(pipex);
	if (msg)
	{
		if (code == 0)
			ft_putstr_fd(msg, 1);
		else
			pi_error(msg, 0);
	}
	exit(code);
}

int	main(int argc, char *argv[])
{
	t_pipex	*pipex;
	int		ret;

	//fprintf(fopen("/Users/jwikiera/Projets/pipex/arglog.txt", "a"), "pipex being run\n");
	pipex = init_pipex();
	if (!pipex)
		handle_exit("failed to initialize pipex struct\n", 1, NULL);
	if (arg_handle(argc, argv, pipex) < 1)
		handle_exit(NULL, 1, pipex);
	ret = 0;
	//print_pipex(pipex);
	if (pipex->is_heredoc)
	{
		//fprintf(fopen("/Users/jwikiera/Projets/pipex/arglog.txt", "a"), "heredoc\n");
		ret = handle_heredoc(pipex);
	}
	else
	{
		//fprintf(fopen("/Users/jwikiera/Projets/pipex/arglog.txt", "a"), "pipes\n");
		ret = handle_pipes(pipex);
	}
	if (ft_file_exists(pipex->commands[pipex->commandc - 1][0]) && !ft_command_ex_current(pipex->commands[pipex->commandc - 1][0], environ))
		ret = 126;
	else if (!ft_command_ex_current(pipex->commands[pipex->commandc - 1][0], environ))
		ret = 127;
	if (pipex->file2_fd == -1)
		ret = 1;
	handle_exit(NULL, ret, pipex);
	return (0);
}
