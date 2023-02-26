/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_heredoc_tempfile.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 11:46:56 by jwikiera          #+#    #+#             */
/*   Updated: 2022/10/11 13:36:27 by jwikiera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*name_from_num(int num)
{
	char	*itoares;
	char	*joinres;

	itoares = ft_itoa(num);
	if (!itoares)
		return (NULL);
	joinres = ft_strjoin("pipex_heredoc_temp", itoares);
	free(itoares);
	return (joinres);
}

char	*get_heredoc_tempfile(void)
{
	int		i;
	char	*joinres;

	if (ft_file_exists("pipex_heredoc_temp"))
	{
		i = 0;
		while (i < INT_MAX)
		{
			joinres = name_from_num(i);
			if (!joinres)
				return (NULL);
			if (!ft_file_exists(joinres))
				return (joinres);
			free(joinres);
			i ++;
		}
	}
	else
		return (ft_strdup("pipex_heredoc_temp"));
	return (NULL);
}
