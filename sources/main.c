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

extern char	**environ;

void	handle_exit(char *msg, int code, t_pipex *pipex)
{
	if (pipex)
		free_pipex(pipex);
	if (msg)
	{
		if (code == 0)
			ft_putstr_fd(msg, 1);
		else
			ft_putstr_fd(msg, 2);
	}
	exit(code);
}

int	main(int argc, char *argv[])
{
	t_pipex	*pipex;

	pipex = init_pipex();
	print_pipex(pipex);
	if (!pipex)
		handle_exit("Failed to initialize pipex struct\n", 1, NULL);
	if (!arg_handle(argc, argv, pipex))
		handle_exit("Invalid arguments\n", 2, pipex);
	print_pipex(pipex);
	if (pipex->is_heredoc)
		handle_heredoc(pipex);
	else
		handle_pipes(pipex);
	handle_exit(NULL, 0, pipex);
	return (0);
}
