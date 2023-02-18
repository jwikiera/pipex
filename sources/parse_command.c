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

int	return_free_split(char **split_res)
{
	ft_free_split(split_res, ft_strarrlen(split_res));
	return (0);
}

int	add_split_to_com_lst(char *ap_split_i, t_list **com_lst)
{
	char	**split_res;
	int		i;
	t_list	*child;
	char	*child_content;

	split_res = ft_split(ap_split_i, ' ');
	if (!split_res)
		return (0);
	i = 0;
	while (split_res[i])
	{
		child_content = malloc(sizeof(*child_content)
				* (ft_strlen(split_res[i]) + 1));
		if (!child_content)
			return (return_free_split(split_res));
		ft_strlcpy(child_content, split_res[i], ft_strlen(split_res[i]) + 1);
		child = ft_lstnew(child_content);
		if (!child)
			return (return_free_split(split_res));
		ft_lstadd_back(com_lst, child);
		i ++;
	}
	ft_free_split(split_res, ft_strarrlen(split_res));
	return (1);
}

static int	add_to_com_lst(char *ap_split_i, t_list **com_lst)
{
	t_list	*child;
	char	*child_content;

	child_content = malloc(sizeof(*child_content)
			* (ft_strlen(ap_split_i) + 1));
	if (!child_content)
		return (0);
	ft_strlcpy(child_content, ap_split_i, ft_strlen(ap_split_i) + 1);
	child = ft_lstnew(child_content);
	if (!child)
		return (0);
	ft_lstadd_back(com_lst, child);
	return (1);
}

static	int	handle_split(char *command, char **ap_split,
				int i, t_list **com_lst)
{
	size_t	j;
	int		found;

	j = 1;
	found = 0;
	while (ft_strlen(command) > 0 && j < ft_strlen(command) - 1
		&& ft_strlen(command + j) > ft_strlen(ap_split[i]))
	{
		if (command[j] == '"' && !ft_strncmp(command + j + 1, ap_split[i],
				ft_strlen(ap_split[i])) && command[j + 1
				+ ft_strlen(ap_split[i])] == '"')
		{
			if (!add_to_com_lst(ap_split[i], com_lst))
				return (0);
			found = 1;
		}
		j ++;
	}
	if (!found)
		return (add_split_to_com_lst(ap_split[i], com_lst));
	return (1);
}

char	**parse_command(char *command)
{
	char	**ap_split;
	int		i;
	t_list	*com_lst;
	char	**res;

	com_lst = NULL;
	ap_split = ft_split(command, '"');
	if (!ap_split)
		return (NULL);
	i = 0;
	while (ap_split[i])
	{
		if (!ft_isblankstr(ap_split[i])
			&& !handle_split(command, ap_split, i, &com_lst))
		{
			ft_free_split(ap_split, ft_strarrlen(ap_split));
			return (NULL);
		}
		i ++;
	}
	ft_free_split(ap_split, ft_strarrlen(ap_split));
	res = ft_tlst_to_strarr(com_lst);
	ft_lstclear(&com_lst, pipex_del_node);
	return (res);
}
