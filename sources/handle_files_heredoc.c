/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_files_heredoc.c                             :+:      :+:    :+:   */
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
/* at first file2 is only created */
/* to read from it, it needs to be reopened */

static int	fd_file1(const char *fname)
{
	if (!fname)
	{
		ft_putstr_fd("fd_file2: fname is NULL\n", 2);
		return (-1);
	}
	return (open(fname, O_WRONLY | O_CREAT | O_APPEND, 0644));
}

int	handle_files_heredoc(const char *fname1, t_pipex *pipex)
{
	pipex->file1_fd = fd_file1(fname1);
	if (pipex->file1_fd == -1)
	{
		ft_putstr_fd("Failed to get file descriptor for file1\n", 2);
		return (0);
	}
	pipex->heredoc_fname = get_heredoc_tempfile();
	if (!pipex->heredoc_fname)
		return (0);
	pipex->file2_fd = fd_file1(pipex->heredoc_fname);
	if (pipex->file2_fd == -1)
	{
		ft_putstr_fd("Failed to get file descriptor for file2\n", 2);
		return (0);
	}
	return (1);
}
