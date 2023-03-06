/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quotesplit2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 11:46:56 by jwikiera          #+#    #+#             */
/*   Updated: 2022/10/11 13:36:27 by jwikiera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*static int	remove_specials(char ***splt)
{
	(void) splt;
	return 0;
}*/

/* slice by isspace */
static int	get_next_token(char *s, char **child_content)
{
	t_list	*word;
	char	c;
	int		i;

	i = 0;
	word = NULL;
	c = ' ';
	*child_content = NULL;
	while(s[i] && c != '!')
	{
		if (c == ' ' && s[i] == '"'
			&& !ft_chr_escaped(i, s))
			c = '"';
		else if (c == ' ' && s[i] == '\''
				 && !ft_chr_escaped(i, s))
			c = '\'';
		else if (((ft_isspace(c) && ft_isspace(s[i]))
				|| (c == '"' && s[i] == '"') || (c == '\'' && s[i] == '\''))
				 && !ft_chr_escaped(i, s))
			c = '!';
		if (s[i] != ft_isspace(c) && !ft_lstadd_chr(s[i], &word))
		{
			ft_lstclear(&word, ft_delnode);
			return (-1);
		}
		i ++;
	}
	*child_content = ft_tlst_to_str(word);
	ft_lstclear(&word, ft_delnode);
	return ((int)ft_strlen(*child_content));
}

static int	add_next_word(char *str_, t_list **tokenlst)
{
	char	*child_content;
	int		added;

	child_content = NULL;
	added = get_next_token(str_, &child_content);
	if (!child_content)
		return (-1);
	if (!ft_lstadd_str(child_content, tokenlst))
		return (-1);
	return (added);
}

char	**ft_quotesplit2(char *str)
{
	t_list	*tokenlst;
	size_t	i;
	char	**res;
	int		added;

	tokenlst = NULL;
	i = 0;
	while (i < ft_strlen(str))
	{
		added = add_next_word(str + i, &tokenlst);
		if (added == -1)
		{
			ft_lstclear(&tokenlst, ft_delnode);
			return (NULL);
		}
		i += added;
	}
	res = ft_tlst_to_strarr(tokenlst);
	ft_lstclear(&tokenlst, ft_delnode);
	return (res);
}
