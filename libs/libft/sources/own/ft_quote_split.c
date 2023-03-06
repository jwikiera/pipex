/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quote_split.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 11:46:56 by jwikiera          #+#    #+#             */
/*   Updated: 2022/10/11 13:36:27 by jwikiera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* 0 = fail, 1 = OK, 2 = continue */
static int	wordbuffer2wordlst(t_list **current_word_chrs, t_list **word_lst)
{
	char	*word;

	if (*current_word_chrs == NULL)
		return (1);
	ft_remove_chr_lst(current_word_chrs, '\\');
	word = ft_tlst_to_str(*current_word_chrs);
	ft_lstclear(current_word_chrs, ft_delnode);
	*current_word_chrs = NULL;
	if (!word)
	{
		ft_lstclear(word_lst, ft_delnode);
		return (0);
	}
	if (!ft_lstadd_str(word, word_lst))
	{
		ft_lstclear(current_word_chrs, ft_delnode);
		ft_lstclear(word_lst, ft_delnode);
		return (0);
	}
	return (1);
}

static int	else_case(char str_i, t_list **current_word_chrs, t_list **word_lst)
{
	if (!ft_lstadd_chr(str_i, current_word_chrs))
	{
		ft_lstclear(current_word_chrs, ft_delnode);
		ft_lstclear(word_lst, ft_delnode);
		return (0);
	}
	return (1);
}

static char	**ret_proxy(t_list **word_lst)
{
	char	**res;

	res = ft_tlst_to_strarr(*word_lst);
	ft_lstclear(word_lst, ft_delnode);
	return (res);
}

int	one_loop(int *current_sep, char str_i, const char *set, t_list **lsts[2])
{
	t_list	**current_word_chrs;
	t_list	**word_lst;

	current_word_chrs = (lsts[0]);
	word_lst = (lsts[1]);
	if (*current_sep == -1 && ft_chr_in_str(str_i, set))
	{
		*current_sep = str_i;
		if (!wordbuffer2wordlst(current_word_chrs, word_lst))
			return (0);
	}
	else if (*current_sep != -1 && str_i == *current_sep && (!ft_lst_get(*current_word_chrs, -1) || (ft_lst_get(*current_word_chrs, -1) && ((char *)ft_lst_get(*current_word_chrs, -1)->content)[0] != '\\')))
	{
		*current_sep = -1;
		if (!wordbuffer2wordlst(current_word_chrs, word_lst))
			return (0);
	}
	else if (ft_isspace(str_i) && *current_sep == -1)
	{
		if (!wordbuffer2wordlst(current_word_chrs, word_lst))
			return (0);
	}
	else if (!else_case(str_i, current_word_chrs, word_lst))
		return (0);
	return (1);
}

char	**ft_quote_split(const char *str, const char *set)
{
	t_list	*word_lst;
	t_list	*current_word_chrs;
	size_t	i;
	int		current_sep;
	t_list	**lsts[2];

	lsts[0] = &current_word_chrs;
	lsts[1] = &word_lst;
	current_word_chrs = NULL;
	word_lst = NULL;
	i = 0;
	current_sep = -1;
	while (str[i])
	{
		if (!one_loop(&current_sep, str[i], set, lsts))
			return (NULL);
		i ++;
	}
	if (!wordbuffer2wordlst(&current_word_chrs, &word_lst))
		return (NULL);
	return (ret_proxy(&word_lst));
}
