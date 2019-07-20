/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alkozma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 17:16:18 by alkozma           #+#    #+#             */
/*   Updated: 2019/07/16 13:15:03 by alkozma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;

	i = 0;
	while (*s1 && (*s1 == *s2) && i < n)
	{
		i++;
		if (i < n)
		{
			s1++;
			s2++;
		}
	}
	return (*(const unsigned char*)s1 - *(const unsigned char*)s2);
}
