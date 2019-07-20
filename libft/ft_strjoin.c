/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alkozma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 14:15:48 by alkozma           #+#    #+#             */
/*   Updated: 2019/07/20 12:54:36 by alkozma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	sz;
	size_t	s1sz;
	size_t	s2sz;
	char	*ret;

	s1sz = ft_strlen(s1);
	s2sz = ft_strlen(s2);
	sz = s1sz + s2sz;
	ret = malloc(sizeof(char) * (sz + 1));
	ft_memcpy(ret, s1, s1sz);
	ft_memcpy(ret + s1sz, s2, s2sz);
	ret[sz] = 0;
	return (ret);
}

char	*ft_strjoin_tok(char const *s1, char const *s2, char tok)
{
	char	*ret;
	int		i;

	i = 0;
	ret = 0;
	if (s1 && s2)
	{
		if (!(ret = (char*)malloc(ft_strlen(s1) + ft_strlen(s2) + 2)))
			return (NULL);
		while (*s1)
			ret[i++] = *s1++;
		ret[i++] = tok;
		while (*s2)
			ret[i++] = *s2++;
		ret[i] = '\0';
	}
	return (ret);
}

char	*ft_strjoin_array(char **arr, char tok)
{
	char	*ret;
	int		i;
	char	*tmp;

	i = 0;
	ret = ft_strnew(0);
	while (arr[i])
	{
		tmp = ft_strjoin_tok(ret, arr[i], tok);
		free(ret);
		ret = tmp;
		i++;
	}
	return (ret);
}
