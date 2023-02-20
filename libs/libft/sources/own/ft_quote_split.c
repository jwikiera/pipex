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

static int	add_char_child(char c, t_list **lst)
{
	t_list	*child;

	child = ft_lstnew(c);
	return (1);
}

char	**ft_quote_split(const char *str, const char *set)
{
	t_list	*current_word_chrs;
	size_t	i;
	int		current_sep;

	current_word_chrs = NULL;
	i = 0;
	current_sep = -1;
	while (str[i])
	{
		if (current_sep == -1 && !ft_chr_in_str(str[i], set))
		{

		}
		i ++;
	}
}
