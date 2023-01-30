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

extern char **environ;

int	main(int argc, char *argv[])
{
	int	i;
	(void) argc;
	(void) argv;
	ft_printf("hello\n");
	i = 0;
	while (environ[i])
	{
		ft_printf("environ[%d]: %s\n", i, environ[i]);
		i ++;
	}
	ft_printf("strerror 69 is %s\n", strerror(69));
	ft_printf("strerror 420 is %s\n", strerror(420));
	return (0);
}
