/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alkozma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/13 15:04:59 by alkozma           #+#    #+#             */
/*   Updated: 2019/07/20 13:27:12 by alkozma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

unsigned long	ft_hash(unsigned char *str)
{
	unsigned long	hash;
	int				i;

	i = 0;
	hash = 5381;
	if (!str || !*str)
		return (0);
	while (str[i])
		hash = ((hash << 5) + hash) + str[i++];
	return (hash % MAX_ENV);
}

void			free_env(t_minishell **in)
{
	t_minishell	*tmp;
	int			i;
	int			found;

	found = 0;
	i = 0;
	tmp = *in;
	while (tmp->hashes[i])
	{
		if (tmp->values[tmp->hashes[i]])
		{
			free(tmp->values[tmp->hashes[i]]);
			tmp->values[tmp->hashes[i]] = NULL;
			found++;
		}
		i++;
	}
	*in = tmp;
}

void			add_hash(t_minishell **in, unsigned long hash)
{
	int			i;
	t_minishell	*tmp;

	i = 0;
	tmp = *in;
	while (tmp->hashes[i] > 0)
		i++;
	tmp->hashes[i] = hash;
	*in = tmp;
}

void			hash_env(t_minishell **in)
{
	int				i;
	t_minishell		*tmp;
	unsigned long	hash;
	char			**buf;

	i = 0;
	tmp = *in;
	buf = NULL;
	ft_bzero(tmp->values, MAX_ENV);
	while (environ[i])
	{
		buf = ft_strsplit(environ[i], '=');
		hash = ft_hash((unsigned char*)buf[0]);
		if (tmp->values[hash % MAX_ENV])
			free(tmp->values[hash % MAX_ENV]);
		tmp->values[hash % MAX_ENV] = ft_strdup(buf[1]);
		add_hash(in, hash);
		ft_strsplit_free(buf);
		environ[i] = ft_strdup(environ[i]);
		i++;
	}
	g_ref = tmp;
	signal(SIGINT, sigint_handler);
	*in = tmp;
}

int				main(void)
{
	char		buf[5000];
	t_minishell	*in;
	int			i;

	in = (t_minishell*)malloc(sizeof(t_minishell));
	in->argv = NULL;
	hash_env(&in);
	while (print_prompt(in) && (i = read(0, buf, 5000)) != 0)
	{
		buf[i - 1] = '\0';
		i = 0;
		while (ft_isspace(buf[i]))
			i++;
		if (buf[i] != 0)
		{
			if (!ft_strcmp(buf + i, "exit"))
			{
				free_env(&in);
				free(in);
				malloced_environ(0) ? ft_strsplit_free(environ) : 0;
				return (1);
			}
			read_input(buf + i, &in);
		}
	}
}
