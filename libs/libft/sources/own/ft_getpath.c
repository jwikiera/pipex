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

/* checks if a string starts with ./ */
static int	starts_with_cr(const char *str)
{
	if (ft_strlen(str) < 2)
		return (0);
	return (str[0] == '.' && str[1] == ft_getsep());
}

static char	*get_abs(const char *binname, char **envp)
{
	char	*basename;
	char	*res;

	basename = ft_basename(binname);
	res = ft_getpath(basename, envp);
	free(basename);
	return (res);
}

/*
 * If available, returns the path of a given binary.
 * Current directory (./) is excluded.
 * Any other form of relative path is made absolute.
 * Ex: /usr/bin/../bin/ls -> /usr/bin/ls
 * */
char	*ft_getpath(const char *binname, char **envp)
{
	char	**path_strarr;
	char	*full_path;
	size_t	i;

	if (!binname || !envp)
		return (NULL);
	if (!starts_with_cr(binname) && ft_file_isex(binname))
		return (get_abs(binname, envp));
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
	return (free_path_strarr(path_strarr));
}
