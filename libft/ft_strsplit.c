/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alkozma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 14:37:12 by alkozma           #+#    #+#             */
/*   Updated: 2019/07/20 07:20:14 by alkozma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			elem_count(char const *s, char c)
{
	int	ret;

	ret = 1;
	while (s && *s)
		if (*s++ == c)
			ret++;
	return (ret);
}

char		**ft_strsplit(char const *s, char c)
{
	int		elems;
	char	**ret;
	int		i;
	int		cur;
	int		os;

	elems = elem_count(s, c);
	ret = ft_memalloc(sizeof(char*) * (elems + 1));
	ret[elems] = NULL;
	i = 0;
	os = 0;
	cur = 0;
	while (i < elems && s && s[cur])
	{
		while (s[cur] && s[cur] != c)
			cur++;
		ret[i++] = ft_strsub(s, os, cur++ - os);
		os = cur;
	}
	return (ret);
}

void		ft_strsplit_free(char **a)
{
	int	i;

	i = 0;
	while (a[i])
	{
		free(a[i]);
		i++;
	}
	free(a);
}
