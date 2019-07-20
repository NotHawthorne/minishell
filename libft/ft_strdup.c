/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alkozma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 10:11:56 by alkozma           #+#    #+#             */
/*   Updated: 2019/07/09 15:10:57 by alkozma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*ret;
	int		len;
	int		i;

	len = ft_strlen(s1);
	ret = (char*)ft_memalloc((len + 1) * sizeof(char));
	i = -1;
	while (s1 && s1[++i])
		ret[i] = s1[i];
	ret[i] = '\0';
	return (ret);
}
