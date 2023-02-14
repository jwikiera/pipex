/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_files.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 11:46:56 by jwikiera          #+#    #+#             */
/*   Updated: 2022/10/11 13:36:27 by jwikiera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/* access in this case also tells us if the file exists */
int	fd_file1(const char *fname)
{
	if (!fname)
	{
		ft_putstr_fd("fd_file1: fname is NULL\n", 2);
		return (-1);
	}
	if (access(fname, R_OK) == -1)
	{
		ft_putstr_fd("fd_file1: file not accessible or does not exist\n", 2);
		return (-1);
	}
	return (open(fname, O_RDONLY));
}

int	fd_file2(const char *fname)
{
	if (!fname)
	{
		ft_putstr_fd("fd_file2: fname is NULL\n", 2);
		return (-1);
	}
	return (open(fname, O_WRONLY | O_CREAT | O_TRUNC, 0644));
}

int	handle_files(const char *fname1, const char *fname2, t_pipex *pipex)
{
	pipex->file1_fd = fd_file1(fname1);
	if (pipex->file1_fd == -1)
	{
		ft_putstr_fd("Failed to get file descriptor for file1\n", 2);
		return (0);
	}
	pipex->file2_fd = fd_file2(fname2);
	if (pipex->file2_fd == -1)
	{
		ft_putstr_fd("Failed to get file descriptor for file2\n", 2);
		return (0);
	}
	return (1);
}

