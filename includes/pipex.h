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
# include <sys/wait.h>

# include <libft.h>
# include <ft_printf.h>

extern char	**environ;

typedef struct s_pipex
{
	int		is_heredoc;
	char	**heredoc_args;
	size_t	heredoc_argc;
	int		file1_fd;
	int		file2_fd;
	char	***commands;
	size_t	commandc;
}	t_pipex;

t_pipex	*init_pipex(void);
void	free_pipex(t_pipex *pipex);
int		arg_handle(int argc, char *argv[], t_pipex *pipex);
int		fd_file1(const char *fname);
int		fd_file2(const char *fname);
int		handle_files(const char *fname1, const char *fname2, t_pipex *pipex);
int		print_pipex(t_pipex *pipex);
int		handle_pipes(t_pipex *pipex);
int		pipe_handler_ret(int status, t_list **pipes);
void	handle_heredoc(t_pipex *pipex);
char	**parse_command(char *command);
void	pipex_del_node(void *content);
int		pi_error(char *msg, int ret);
int		heredoc_arg_handle(int argc, char *argv[], t_pipex *pipex);

#endif
