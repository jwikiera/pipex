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

	pipex = init_pipex();
	if (!pipex)
		handle_exit("failed to initialize pipex struct\n", 1, NULL);
	if (!arg_handle(argc, argv, pipex))
		handle_exit("invalid arguments\n", 2, pipex);
	ret = 0;
	if (pipex->is_heredoc)
		ret = handle_heredoc(pipex);
	else
		ret = handle_pipes(pipex);
	if (!ft_command_ex_current(pipex->commands[pipex->commandc - 1][0], environ))
		ret = 127;
	if (pipex->file2_fd == -1)
		ret = 1;
	handle_exit(NULL, ret, pipex);
	return (0);
}
