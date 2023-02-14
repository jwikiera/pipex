/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 11:46:56 by jwikiera          #+#    #+#             */
/*   Updated: 2022/10/11 13:36:27 by jwikiera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	print_pipex(t_pipex *pipex)
{
	if (!ft_printf("pipex struct @%x\n", pipex))
		return (0);
	if (!ft_printf("file1_fd: %d\n", pipex->file1_fd))
		return (0);
	if (!ft_printf("file2_fd: %d\n", pipex->file2_fd))
		return (0);
	if (!ft_printf("commands: "))
		return (0);
	if (!ft_print_strarr(pipex->commands, pipex->commandc, 0))
		return (0);
	if (!ft_printf("\ncommandc: %d\n", pipex->commandc))
		return (0);
	if (!ft_printf("is_heredoc: %d\n", pipex->is_heredoc))
		return (0);
	if (!ft_printf("heredoc_args: "))
		return (0);
	if (!ft_print_strarr(pipex->heredoc_args, pipex->heredoc_argc, 0))
		return (0);
	if (!ft_printf("\nheredoc_argc: %d\n", pipex->heredoc_argc))
		return (0);
	return (1);
}
