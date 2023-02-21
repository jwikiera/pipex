/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getpath.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 11:46:56 by jwikiera          #+#    #+#             */
/*   Updated: 2022/10/11 13:36:27 by jwikiera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*free_path_strarr(char **path_strarr)
{
	ft_free_split(path_strarr,
		ft_strarrlen(path_strarr));
	return (NULL);
}

/*
 * If available, returns the path of a given binary.
 * */
char	*ft_getpath(const char *binname, char **envp)
{
	char	**path_strarr;
	char	*full_path;
	size_t	i;

	if (!binname || !envp)
		return (NULL);
	path_strarr = ft_environ_to_path_strarr(envp);
	if (!path_strarr)
		return (NULL);
	i = 0;
	while (path_strarr[i])
	{
		if (ft_bin_in_path(binname, path_strarr[i]))
		{
			full_path = ft_joinpaths(path_strarr[i], binname, NULL);
			free_path_strarr(path_strarr);
			return (full_path);
		}
		i ++;
	}
	ft_free_split(path_strarr,
		ft_strarrlen(path_strarr));
	return (free_path_strarr(path_strarr));
}
