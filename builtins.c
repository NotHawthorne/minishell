/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alkozma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/13 15:59:05 by alkozma           #+#    #+#             */
/*   Updated: 2019/07/20 13:30:03 by alkozma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	update_pwd(t_minishell *in)
{
	unsigned long	hash;
	char			buf[5000];

	hash = ft_hash((unsigned char*)("PWD"));
	if (in->values[hash])
	{
		if (in->values[ft_hash((unsigned char*)("OLDPWD"))])
			free(in->values[ft_hash((unsigned char*)("OLDPWD"))]);
		in->values[ft_hash((unsigned char*)("OLDPWD"))] =
			ft_strdup(in->values[hash]);
		free(in->values[hash]);
	}
	ft_memset(buf, 0, 5000);
	getcwd(buf, 5000);
	in->values[hash] = ft_strdup(buf);
	return (1);
}

static int	update_oldpwd(t_minishell *in)
{
	unsigned long	hash;
	char			buf[5000];

	hash = ft_hash((unsigned char*)("OLDPWD"));
	if (in->values[hash])
		free(in->values[hash]);
	ft_memset(buf, 0, 5000);
	getcwd(buf, 5000);
	in->values[hash] = ft_strdup(buf);
	return (1);
}

static int	go_home(t_minishell *in)
{
	ft_setenv("OLDPWD", in->values[ft_hash((unsigned char*)("PWD"))], in);
	ft_setenv("PWD", in->values[ft_hash((unsigned char*)("HOME"))], in);
	return (chdir(in->values[ft_hash((unsigned char*)("HOME"))]));
}

int			ft_cd(t_minishell *in)
{
	unsigned long	hash;
	char			*old;

	hash = ft_hash((unsigned char*)("OLDPWD"));
	old = in->argv[1] && !ft_strcmp(in->argv[1], "-")
		? ft_strdup(in->values[hash]) : 0;
	update_oldpwd(in);
	if (!in->argv[1])
		go_home(in);
	else if (!ft_strcmp(in->argv[1], "-"))
	{
		if (!old || !*old)
			return (ft_printf("minishell: cd: OLDPWD not set\n"));
		ft_setenv("PWD", old, in);
		chdir(old) < 0 ? ft_printf("%s\n", strerror(errno)) : 0;
		free(old);
		return (1);
	}
	else if (chdir(in->argv[1]) < 0)
		return (ft_printf("minishell: cd: %s: %s\n",
					in->argv[1], strerror(errno)));
	else
		return (update_pwd(in));
	return (0);
}

int			check_builtins(t_minishell *in)
{
	int	i;

	i = 0;
	if (!ft_strcmp(in->argv[0], "cd"))
		return (ft_cd(in));
	if (!ft_strcmp(in->argv[0], "setenv") && in->argv[1] && in->argv[2])
		return (ft_setenv(in->argv[1], in->argv[2], in));
	if (!ft_strcmp(in->argv[0], "unsetenv") && in->argv[1])
		return (ft_unsetenv(in->argv[1], in));
	if (!ft_strcmp(in->argv[0], "echo"))
	{
		while (in->argv[i + 1])
		{
			if (in->argv[i + 1][0] > 0)
				ft_printf("%s%s", in->argv[i + 1], in->argv[i + 2] ? " " : "");
			i++;
		}
		ft_printf("\n");
		return (1);
	}
	if (!ft_strcmp(in->argv[0], "senpai"))
		return (ft_printf("\n%s\n", DEGENERACY));
	return (0);
}
