/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_equal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 11:12:16 by jwikiera          #+#    #+#             */
/*   Updated: 2022/10/20 11:12:18 by jwikiera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	hrdceq(const char *str, const char *limiter)
{
	char	*trimmed;
	int		res;

	if (ft_strlen(limiter) == 0
		&& ft_strlen(str) == 1 && str[0] == '\n')
		return (1);
	trimmed = ft_powertrim(str, "");
	if (!trimmed)
		return (1);
	res = ft_strequal(trimmed, limiter);
	free(trimmed);
	return (res);
}
