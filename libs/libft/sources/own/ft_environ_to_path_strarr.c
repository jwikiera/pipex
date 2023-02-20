/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_environ_to_path_strarr.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 11:12:16 by jwikiera          #+#    #+#             */
/*   Updated: 2022/10/20 11:12:18 by jwikiera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**final_ret(char *pth)
{
	char	**scnd_split_res;

	if (ft_strlen(pth) < ft_strlen("PATH="))
		return (NULL);
	return(ft_split(pth + ft_strlen("PATH="), ':'));
}

char	**ft_environ_to_path_strarr(const char *envp)
{
	t_list	*lst;
	char	**res;
	char	**split_res;
	size_t	i;

	res = NULL;
	if (!envp)
		return (NULL);
	split_res = ft_split(envp, '\n');
	if (!split_res)
		return (NULL);
	i = 0;
	while (i < ft_strarrlen(split_res)
			&& ft_strncmp(split_res[i], "PATH", ft_strlen("PATH")))
		i ++;
	if (i == ft_strarrlen(split_res))
		return (NULL);
	res = final_ret(split_res[i]);
	ft_free_split(split_res, ft_strarrlen(split_res));
	return (res);
}
