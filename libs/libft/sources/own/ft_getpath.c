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

static char	*free_path_strarr(char **path_strarr, char *basename)
{
	if (basename)
		free(basename);
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

static char	*abs_local_ret(const char *binname, char **envp)
{
	char	*basename;
	char	*joined;
	char	*pwd;

	basename = ft_basename(binname);
	if (!basename)
		return (NULL);
	pwd = ft_pwd(envp);
	if (!pwd)
	{
		free(basename);
		return (NULL);
	}
	joined = ft_joinpaths(pwd, basename, NULL);
	free(pwd);
	free(basename);
	return (joined);
}

static char	*get_abs(const char *binname, char **path_strarr, char **envp)
{
	char	*basename;
	size_t	i;
	char	*full_path;

	if (starts_with_cr(binname) && ft_file_isex(binname))
		return (abs_local_ret(binname, envp));
	//TODO: make function to check if pwd + basename is an executable. If yes, return NULL
	else if (!starts_with_cr(binname) &&  && ft_file_isex(binname))
		return (ft_strdup(binname));
	basename = ft_basename(binname);
	if (!basename)
		return (NULL);
	i = 0;
	while (path_strarr[i])
	{
		if (ft_bin_in_path(basename, path_strarr[i]))
		{
			full_path = ft_joinpaths(path_strarr[i], basename, NULL);
			free_path_strarr(path_strarr, basename);
			return (full_path);
		}
		i ++;
	}
	return (free_path_strarr(path_strarr, basename));
}

/*
 * If available, returns the path of a given binary.
 * Current directory (./) is excluded.
 * Any other form of relative path is made absolute.
 * Ex: /usr/bin/../bin/ls -> /usr/bin/ls
 * */
//TODO: apparently there is a leak here
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
	if (ft_str_startswith(binname, "/") && ft_file_isex(binname))
		return (ft_strdup(binname));
	if (/*!starts_with_cr(binname) &&*/ ft_file_isex(binname))
	{
		fprintf(stderr, "bruh: %s\n", binname);
		return (get_abs(binname, path_strarr, envp));
	}
	if (starts_with_cr(binname) && !ft_file_isex(binname))
		return (NULL);
	i = 0;
	while (path_strarr[i])
	{
		if (ft_bin_in_path(binname, path_strarr[i]))
		{
			full_path = ft_joinpaths(path_strarr[i], binname, NULL);
			free_path_strarr(path_strarr, NULL);
			return (full_path);
		}
		i ++;
	}
	return (free_path_strarr(path_strarr, NULL));
}
