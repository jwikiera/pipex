/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_joinpaths.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 11:46:56 by jwikiera          #+#    #+#             */
/*   Updated: 2022/10/11 13:36:27 by jwikiera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	lst_add_first(const char *frst, t_list **lst)
{
	int		had_sep;
	char	*blank_trimmed;
	char	*all_trimmed;
	char	*sep_joined;

	blank_trimmed = ft_powertrim(frst, "");
	if (!blank_trimmed)
		return (0);
	had_sep = blank_trimmed[0] == ft_getsep();
	all_trimmed = ft_powertrim_chr(blank_trimmed, ft_getsep());
	free(blank_trimmed);
	if (!all_trimmed)
		return (0);
	if (had_sep)
	{
		sep_joined = ft_strjoin_chr_str(ft_getsep(), all_trimmed);
		free(all_trimmed);
		if (!sep_joined)
			return (0);
		return (ft_lstadd_str(sep_joined, lst));
	}
	else
		return (ft_lstadd_str(all_trimmed, lst));
}

/* Accepts NULL terminated list of paths */
char	*ft_joinpaths(const char *path, ...)
{
	va_list		ptr;
	size_t		pthcnt;
	t_list		*pth_lst;

	pthcnt = 0;
	pth_lst = NULL;
	va_start(ptr, path);
	ft_putstr_fd("received paths:\n", 1);
	if (!lst_add_first(path, &pth_lst))
		return (0);
	while (path)
	{
		pthcnt ++;
		ft_ptstrfd_s(path, 1);
		ft_ptstrfd_s("\n", 1);
		path = va_arg(ptr, const char *);
	}
	va_end(ptr);
	if (pthcnt == 0)
		return (NULL);
	return (NULL);
}
