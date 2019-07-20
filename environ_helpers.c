/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alkozma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/20 07:46:30 by alkozma           #+#    #+#             */
/*   Updated: 2019/07/20 13:19:59 by alkozma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		malloced_environ(int op)
{
	static int	mallocd;

	if (op)
		return ((mallocd = 1));
	return (mallocd);
}

int		sizeof_environ(void)
{
	int	i;

	i = 0;
	while (environ[i])
		i++;
	return (i);
}

void	sigint_handler(int x)
{
	if (!x)
		return ;
	write(1, "\n", 1);
	print_prompt(g_ref);
}
