/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alkozma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/07 10:32:11 by alkozma           #+#    #+#             */
/*   Updated: 2019/07/21 06:06:53 by alkozma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define DEGENERACY "░░░░░░░░░░░▄▄▀▀▀▀▀▀▀▀▄▄\n░░░░░░░░▄▀▀░░░░░░░░░░░░▀▄▄\n░░░░░░▄▀░░░░░░░░░░░░░░░░░░▀▄\n░░░░░▌░░░░░░░░░░░░░▀▄░░░░░░░▀▀▄\n░░░░▌░░░░░░░░░░░░░░░░▀▌░░░░░░░░▌\n░░░▐░░░░░░░░░░░░▒░░░░░▌░░░░░░░░▐\n░░░▌▐░░░░▐░░░░▐▒▒░░░░░▌░░░░░░░░░▌\n░░▐░▌░░░░▌░░▐░▌▒▒▒░░░▐░░░░░▒░▌▐░▐\n░░▐░▌▒░░░▌▄▄▀▀▌▌▒▒░▒░▐▀▌▀▌▄▒░▐▒▌░▌\n░░░▌▌░▒░░▐▀▄▌▌▐▐▒▒▒▒▐▐▐▒▐▒▌▌░▐▒▌▄▐\n░▄▀▄▐▒▒▒░▌▌▄▀▄▐░▌▌▒▐░▌▄▀▄░▐▒░▐▒▌░▀▄\n▀▄▀▒▒▌▒▒▄▀░▌█▐░░▐▐▀░░░▌█▐░▀▄▐▒▌▌░░░▀\n░▀▀▄▄▐▒▀▄▀░▀▄▀░░░░░░░░▀▄▀▄▀▒▌░▐\n░░░░▀▐▀▄▒▀▄░░░░░░░░▐░░░░░░▀▌▐\n░░░░░░▌▒▌▐▒▀░░░░░░░░░░░░░░▐▒▐\n░░░░░░▐░▐▒▌░░░░▄▄▀▀▀▀▄░░░░▌▒▐\n░░░░░░░▌▐▒▐▄░░░▐▒▒▒▒▒▌░░▄▀▒░▐\n░░░░░░▐░░▌▐▐▀▄░░▀▄▄▄▀░▄▀▐▒░░▐\n░░░░░░▌▌░▌▐░▌▒▀▄▄░░░░▄▌▐░▌▒░▐\n░░░░░▐▒▐░▐▐░▌▒▒▒▒▀▀▄▀▌▐░░▌▒░▌\n░░░░░▌▒▒▌▐▒▌▒▒▒▒▒▒▒▒▐▀▄▌░▐▒▒\n\ns e n p a i   p l s   n o\n"
# define ORANGE "\033[0;0;95;38;5;214m"
# define PROMPT "└λ\033[m"
# define MAX_ENV 10000

# include <unistd.h>
# include <dirent.h>
# include <sys/types.h>
# include <sys/wait.h>
# include "includes/libft.h"
# include "includes/ftprintf.h"
# include "includes/ftgnl.h"
# include <errno.h>
# include <pwd.h>

# include <signal.h>

extern char				**environ;
struct s_minishell		*g_ref;

typedef struct			s_history
{
	char				*input;
	struct s_history	*next;
	struct s_history	*prev;
}						t_history;

typedef struct			s_minishell
{
	char				**argv;
	char				*values[MAX_ENV];
	unsigned long		hashes[MAX_ENV];
	struct s_history	*history;
}						t_minishell;

void				read_input(char *input, t_minishell **in);
void				hash_env(t_minishell **in);
void				add_hash(t_minishell **in, unsigned long hash);
void				exec_program(char *input, t_minishell *in);
void				sigint_handler(int x);
void				hide_quotes(char *str);

char				*accessible(char *fname, t_minishell *in);

int					check_builtins(t_minishell *in);
int					ft_setenv(char *name, char *value, t_minishell *in);
int					ft_unsetenv(char *name, t_minishell *in);
int					malloced_environ(int op);
int					print_prompt(t_minishell *in);
int					sizeof_environ(void);

unsigned long		ft_hash(unsigned char *str);

#endif
