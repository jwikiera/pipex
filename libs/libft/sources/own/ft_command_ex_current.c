/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_command_ex_current.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 11:46:56 by jwikiera          #+#    #+#             */
/*   Updated: 2022/10/11 13:36:27 by jwikiera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_command_ex_current(char *command, char **envp)
{
	char	*res;

	res = ft_getpath_current(command, envp);
	if (res == NULL)
		return (0);
	free(res);
	return (1);
}
