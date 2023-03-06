/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 11:12:16 by jwikiera          #+#    #+#             */
/*   Updated: 2022/10/20 11:12:18 by jwikiera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/* traverses command backwards and checks if it's
 * a valid command by each iter. lazy
 * */

//TODO: mallocs don't add up ?

static char	*get_cmd(char *command)
{
	char	*trimmed;
	size_t	i;
	char	*tmp;

	trimmed = ft_powertrim(command, "");
	if (!trimmed)
		return (NULL);
	i = ft_strlen(trimmed) - 1;
	while (i >= 0)
	{
		tmp = malloc(sizeof (*tmp) * (ft_strlen(trimmed) - i + 1));
		if (!tmp)
			return (NULL);
		ft_memcpy(tmp, trimmed, ft_strlen(trimmed) - i);
		tmp[ft_strlen(trimmed) - i] = '\0';
		if (ft_command_ex_current(trimmed, environ))
		{
			free(trimmed);
			return (tmp);
		}
		free(tmp);
		i --;
	}
	free(trimmed);
	return (NULL);
}

char	**parse_command(char *command)
{
	char	*cmd;
	char	**qspltres;
	char	**joined;

	cmd = get_cmd(command);
	if (!cmd)
		return (NULL);
	qspltres = ft_quote_split(command, "'\"");
	if (!qspltres)
	{
		free(cmd);
		return (NULL);
	}
	joined = ft_prependstr2strarr(cmd, qspltres);
	free(cmd);
	ft_free_split(qspltres, ft_strarrlen(qspltres));
	return (joined);
}
