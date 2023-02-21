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


	/// ---- TEST -------

	char **pth = ft_environ_to_path_strarr(environ);
	ft_println_strarr(pth, 0, 1);

	ft_joinpaths("lol", "lel", NULL);

	/*
	ft_printf("test\n");
	char	**lol = ft_quote_split("awk 'BEGIN { for(i=1;i<=6;i++) print \"square of\", i, \"is\",i*i; }'", "'\"");
	ft_print_strarr(lol, 0, 1);
	ft_printf("\n");
	ft_printf("len of lol: %d\n", ft_strarrlen(lol));
	 */

	//ft_printf("exec res: %d\n", execve("checker", ft_quote_split("lol", ""), environ));

	/*int id;

	id = fork();
	if (id == 0)
	{
		ft_printf("hello from the fork\n");
		ft_print_strarr(ft_quote_split("touch file3", ""), 0, 1);
		//ft_print_strarr(environ, 0, 1);
		ft_printf("\n");
		execve("/bin/ls", ft_quote_split("/bin/ls", ""), environ);
	}
	else
	{
		int res;

		wait(&res);
		ft_printf("errno: %d\n", errno);
		ft_printf("wait res: %d\n", res);

		ft_println_strarr(environ, 0, 1);
		char **pth = ft_environ_to_path_strarr((const char *) environ);
		ft_println_strarr(pth, 0, 1);
	}*/

	/// ---- END TEST ---


	handle_exit(NULL, 0, pipex);
	return (0);
}
