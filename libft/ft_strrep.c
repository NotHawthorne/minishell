/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alkozma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 11:38:21 by alkozma           #+#    #+#             */
/*   Updated: 2019/07/20 12:56:44 by alkozma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "../includes/ftprintf.h"

int			alk_substr_count(const char *str, const char *sub)
{
	int		i;
	int		elems;
	size_t	sublen;

	elems = 0;
	i = 0;
	sublen = ft_strlen(sub);
	while (str[i])
		if (!ft_strncmp(str + i++, sub, sublen))
			elems++;
	return (elems);
}

static int	calculate_size(const char *str, const char *sub, const char *rep)
{
	return (ft_strlen(str) - (ft_strlen(sub) * alk_substr_count(str, sub))
			+ (ft_strlen(rep) * alk_substr_count(str, sub)));
}

char		*ft_strrep(const char *str, const char *sub, const char *rep)
{
	char	*ret;
	size_t	sublen;
	int		i;
	int		offset;

	(!(*rep)) ? rep = "\0" : 0;
	ret = malloc(calculate_size(str, sub, rep));
	sublen = ft_strlen(sub);
	i = 0;
	offset = 0;
	while (str[i])
	{
		if (!ft_strncmp(str + i, sub, sublen))
		{
			ft_memcpy(ret + i + offset, rep, ft_strlen(rep));
			i += (sublen - 1);
			offset += sublen > ft_strlen(rep) ? sublen - ft_strlen(rep)
				: ft_strlen(rep) - sublen;
		}
		else
			ret[i + offset] = str[i];
		i++;
	}
	ret[i + offset] = '\0';
	return (ret);
}
