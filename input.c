/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alkozma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/13 15:42:44 by alkozma           #+#    #+#             */
/*   Updated: 2019/07/20 13:28:06 by alkozma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	replace_home(char **str, t_minishell **in)
{
	t_minishell	*tmp;
	char		*ret;
	char		*buf;

	tmp = *in;
	ret = *str;
	if (ret[0] == '~' && (!ret[1] || ret[1] == '/'))
	{
		buf = ft_strrep(ret, "~",
				tmp->values[ft_hash((unsigned char*)("HOME"))]);
		free(ret);
		ret = buf;
	}
	*str = ret;
	*in = tmp;
}

void	replace_env(char **str, t_minishell **in)
{
	t_minishell	*tmp;
	char		*ret;
	char		*buf;

	tmp = *in;
	ret = *str;
	if (ret[0] == '$')
	{
		if (!tmp->values[ft_hash((unsigned char*)(ret + 1))])
			buf = ft_strrep(ret, ret, "\0");
		else
			buf = ft_strrep(ret, ret,
					tmp->values[ft_hash((unsigned char*)(ret + 1))]);
		free(ret);
		ret = ft_strdup(buf);
		free(buf);
	}
	*str = ret;
	*in = tmp;
}

void	replace_tokens(t_minishell **in)
{
	int			i;
	t_minishell	*tmp;

	tmp = *in;
	i = 0;
	while (tmp->argv[i])
	{
		if (tmp->argv[i] && !ft_isspace(tmp->argv[i][0]))
		{
			replace_home(&(tmp->argv[i]), in);
			replace_env(&(tmp->argv[i]), in);
		}
		i++;
	}
	*in = tmp;
}

void	read_input(char *input, t_minishell **sh)
{
	t_minishell			*in;
	char				*dir;
	int					i;

	in = *sh;
	input = ft_strtrim(input);
	in->argv = ft_strsplit(input, ' ');
	replace_tokens(&in);
	dir = NULL;
	if (!check_builtins(in))
	{
		i = 0;
		while (in->argv[0][i])
			if (ft_isspace(in->argv[0][i++]))
				in->argv[0][i - 1] = '\0';
		if ((dir = accessible(in->argv[0], in)))
			exec_program(dir, in);
		else
			ft_printf("minishell: %s: command not found\n", in->argv[0]);
	}
	free(input);
	ft_strsplit_free(in->argv);
	if (dir)
		free(dir);
	*sh = in;
}
