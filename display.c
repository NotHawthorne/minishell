/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alkozma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/20 07:37:03 by alkozma           #+#    #+#             */
/*   Updated: 2019/07/20 07:39:12 by alkozma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				print_prompt(t_minishell *in)
{
	ft_printf("%s┌[\033[m%s%s]\n%s ",
		ORANGE, in->values[ft_hash((unsigned char*)("PWD"))],
		ORANGE, PROMPT);
	return (1);
}
