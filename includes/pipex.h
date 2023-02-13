/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 11:46:56 by jwikiera          #+#    #+#             */
/*   Updated: 2022/10/11 13:36:27 by jwikiera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# ifdef LINUX
# else
# endif

# include "stdlib.h"
# include "stdio.h"
# include "unistd.h"
# include "string.h"
# include "fcntl.h"

# include <libft.h>
# include <ft_printf.h>

typedef struct s_pipex
{
	char	**heredoc_args;
	size_t	heredoc_argc;
	int		file1_fd;
	int		file2_fd;
	char	**commands;
	size_t	commandc;
}	t_pipex;

t_pipex	*init_pipex();
void	free_pipex(t_pipex *pipex);
int		arg_handle(int argc, char *argv[], t_pipex *pipex);

#endif