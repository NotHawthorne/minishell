/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alkozma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/13 15:17:38 by alkozma           #+#    #+#             */
/*   Updated: 2019/07/20 11:46:58 by alkozma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		env_exists(char *name)
{
	int		i;
	char	**buf;

	i = 0;
	while (environ[i])
	{
		buf = ft_strsplit(environ[i], '=');
		if (!ft_strcmp(name, buf[0]))
		{
			ft_strsplit_free(buf);
			return (i);
		}
		ft_strsplit_free(buf);
		i++;
	}
	return (-1);
}

char	*create_env_str(char *name, char *value, t_minishell *in)
{
	char	*ret;
	int		i;
	int		b;

	i = 0;
	b = 0;
	ret = malloc(sizeof(char) * (ft_strlen(name) + ft_strlen(value) + 2));
	while (name[i])
	{
		ret[i] = name[i];
		i++;
	}
	ret[i++] = '=';
	while (value[b])
		ret[i++] = value[b++];
	ret[i] = '\0';
	if (in->values[ft_hash((unsigned char*)(name))])
		free(in->values[ft_hash((unsigned char*)(name))]);
	in->values[ft_hash((unsigned char*)(name))] = ft_strdup(value);
	return (ret);
}

void	add_new_env(char *name, char *value, t_minishell *in)
{
	int			i;
	char		**ret;

	i = 0;
	while (environ[i])
		i++;
	ret = malloc(sizeof(char*) * (i + 2));
	ret[i] = NULL;
	i = 0;
	while (environ[i])
	{
		ret[i] = ft_strdup(environ[i]);
		malloced_environ(0) ? free(environ[i]) : 0;
		i++;
	}
	ret[i] = create_env_str(name, value, in);
	ret[i + 1] = NULL;
	if (in->values[ft_hash((unsigned char*)(name))])
		free(in->values[ft_hash((unsigned char*)(name))]);
	in->values[ft_hash((unsigned char*)(name))] = ft_strdup(value);
	add_hash(&in, ft_hash((unsigned char*)(name)));
	malloced_environ(0) ? free(environ) : malloced_environ(1);
	environ = ret;
}

int		ft_setenv(char *name, char *value, t_minishell *in)
{
	int				i;

	if ((i = env_exists(name)) >= 0)
	{
		free(environ[i]);
		environ[i] = create_env_str(name, value, in);
	}
	else
		add_new_env(name, value, in);
	return (1);
}

int		ft_unsetenv(char *name, t_minishell *in)
{
	char		**ret;
	int			i;
	int			found;
	char		**buf;

	found = 0;
	if (env_exists(name) >= 0)
	{
		ret = ft_memalloc(sizeof(char*) * sizeof_environ());
		i = -1;
		while (environ[++i])
		{
			buf = ft_strsplit(environ[i], '=');
			ft_strcmp(name, buf[0])
				? ret[i - found] = ft_strdup(environ[i]) : 0;
			ft_strcmp(name, buf[0]) ? 0 : found++;
			ft_strsplit_free(buf);
		}
		malloced_environ(0) ? ft_strsplit_free(environ) : malloced_environ(1);
		environ = ret;
		free(in->values[ft_hash((unsigned char*)name)]);
		in->values[ft_hash((unsigned char*)name)] = NULL;
	}
	return (1);
}
