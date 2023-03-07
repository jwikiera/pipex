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
static int	fd_file1(const char *fname)
{
	char	*joined;
	char	*j2;

	if (!fname)
	{
		ft_putstr_fd("fd_file1: fname is NULL\n", 2);
		return (-1);
	}
	if (access(fname, R_OK) == -1)
	{
		joined = ft_strjoin( fname, ": No such file or directory");
		if (!joined)
			return (-1);
		j2 = ft_strjoin(joined, "\n");
		free(joined);
		if (!j2)
			return (-1);
		pi_error(j2, 0);
		free(j2);
		return (-1);
	}
	return (open(fname, O_RDONLY));
}

static int	fd_file2(const char *fname)
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
	if (0 && pipex->file1_fd == -1)
	{
		return (1);
	}
	pipex->file2_fd = fd_file2(fname2);
	if (pipex->file2_fd == -1)
	{
		return (1);
	}
	return (1);
}
