/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 15:18:02 by jwikiera          #+#    #+#             */
/*   Updated: 2022/10/21 15:18:04 by jwikiera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include "stdio.h"

static int	count_words_set(char const *str, const char *sep)
{
	int	i;
	int	same_word;

	i = 0;
	same_word = 0;
	while (*str)
	{
		if (ft_chr_in_str(*str, sep))
			same_word = 0;
		else
		{
			if (!same_word)
			{
				same_word = 1;
				i ++;
			}
		}
		str ++;
	}
	return (i);
}

static size_t	next_wordlen(char const *str, const char *sep)
{
	int	i;

	i = 0;
	while (*str)
	{
		if (ft_chr_in_str(*str, sep))
			return (i);
		else
			i ++;
		str ++;
	}
	return (i);
}

static char	**handle_empty(void)
{
	char	**res;

	res = malloc(sizeof(*res));
	if (!res)
		return (0);
	res[0] = 0;
	return (res);
}

static int	free_split(char ***res, int index)
{
	int	i;

	if ((*res)[index])
		return (0);
	i = 0;
	while (i < index)
	{
		free((*res)[i]);
		i ++;
	}
	free(res);
	return (1);
}

char	**ft_splitset(char const *str, const char *sep)
{
	char	**res;
	int		i;

	if (!count_words_set(str, sep))
		return (handle_empty());
	res = malloc(sizeof(*res) * (count_words_set(str, sep) + 1));
	if (!res)
		return (0);
	i = 0;
	while (*str)
	{
		if (!ft_chr_in_str(*str, sep))
		{
			res[i] = malloc(next_wordlen(str, sep) + 1);
			if (free_split(&res, i))
				return (0);
			ft_strlcpy(res[i], str, next_wordlen(str, sep) + 1);
			i ++;
			str += next_wordlen(str, sep);
		}
		else
			str ++;
	}
	res[i] = 0;
	return (res);
}
