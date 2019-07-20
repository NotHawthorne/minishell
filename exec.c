/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alkozma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/14 13:26:46 by alkozma           #+#    #+#             */
/*   Updated: 2019/07/20 13:26:49 by alkozma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_or_set(char **src, char *dst)
{
	(*src) ? free(*src) : 0;
	*src = ft_strdup(dst);
}

static void	help_concat_path(char **src, char *path, char *fname)
{
	char	*tmp;

	tmp = ft_strdup(path);
	(*src) ? free(*src) : 0;
	*src = ft_strjoin_tok(path, fname, '/');
	free(tmp);
}

char		*accessible(char *fname, t_minishell *in)
{
	char			**pathdirs;
	struct dirent	*curdir;
	DIR				*dirp;
	char			*ret;
	int				i;

	i = -1;
	if (fname[0] == '/')
		return (ft_strdup(fname));
	ret = ft_strdup(in->values[ft_hash((unsigned char*)("PWD"))]);
	pathdirs = ft_strsplit(in->values[ft_hash((unsigned char*)("PATH"))], ':');
	while (pathdirs[++i])
	{
		if ((dirp = opendir(pathdirs[i])))
		{
			while ((curdir = readdir(dirp)))
				if (ft_strcmp(fname, curdir->d_name) == 0)
					free_or_set(&ret, pathdirs[i]);
			closedir(dirp);
		}
	}
	ft_strsplit_free(pathdirs);
	help_concat_path(&ret, ret, fname);
	return (ret);
}

void		exec_program(char *input, t_minishell *in)
{
	struct rusage	usage;
	int				status;
	int				op;
	int				pid;
	int				pid2;

	op = 0;
	pid = fork();
	pid2 = wait4(pid, &status, op, &usage);
	if (pid == 0)
	{
		if (execve(input, in->argv, environ) < 0)
		{
			ft_printf("minishell: %s: command not found\n", in->argv[0]);
			exit(0);
		}
	}
}
