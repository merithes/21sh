/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboivin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/26 21:25:52 by vboivin           #+#    #+#             */
/*   Updated: 2017/12/02 21:11:36 by vboivin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HMINI_H
# define HMINI_H

# include <sys/stat.h>
# include <sys/param.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <dirent.h>
# include <time.h>
# include <grp.h>
# include <pwd.h>
# include <term.h>
# include <curses.h>
# include "libft.h"

/*
** DEFINED VALUES
** ==============
*/

# define EXIT 55
# define MONE (1)
# define MTWO (1 << 1)
# define MFOU (1 << 2)
# define MPL MAXPATHLEN

# define LEFT 1
# define RIGHT 0

# define MAX_HISTO 25

# define BACKMX "4294967295"

# define N_ENV "Environment received empty. Creating a new one.\n"
# define DEF_PROMPT "[\\s]\\u> "
# define DEF_PATH "/bin:/usr/bin:/usr/local/bin:/sbin:/usr/sbin"

# define NSFOD " No such file or directory\n"
# define NEOB " File doesn't exist or isn't a binary"
# define NSC " No such command\n"

/*
** /!\SYSTEM DEPENDANT /!\
** ============================================================================
*/

/*
** MACROS
** ============================================================================
*/

/*
** TYPEDEFS
*/

typedef struct				s_env
{
	char					*full;
	char					*name;
	char					*cont;
	struct s_env			*next;
}							t_env;

typedef struct				s_histo
{
	char					*cont;
	struct s_histo			*prev;
	struct s_histo			*next;
	int						swit;
}							t_histo;

typedef struct termios		t_ermios;

/*
** GLOBALS
*/

t_ermios					termcap_21sh[2];
t_env						*g_backup_env;

/*
** DECLARATIONS
** ============================================================================
*/

void						write_prompt(t_env *env);
char						*line_env_interpret(char *inp, t_env *env);
char						*skip_cmd(char *inp, int nb);
int							getpath(char *cmd, t_env *env, char *fullpath);

void						cd_bin(char **arr, t_env *env);
void						echo_bin(char **arr, char *cmd, t_env *env);
void						exit_bin(char **arr, char *cmd, t_env *env);

void						uenv_bin(char **arr, t_env *env);
void						env_bin(char **arr, t_env *env);
void						setenv_bin(char **arr, char *cmd, t_env *env);

int							builtin_chk(char **arr, char *cmd, t_env *env);
char						**rmk_env(t_env *inp);
int							env_is_valid(char *inp, char *inp2);
char						*ft_var_brackets(char *str, int allc);

t_env						*translate_env(char *env[], int type);
t_env						*init_env(void);

t_env						*get_env_var(char *to_search, t_env *list);
char						*get_cut_env(char *inp, int type);
t_env						*new_var(t_env *root, char *name,
								char *content, int allc);
t_env						*create_root_var(void);

void						increment_shlvl(t_env *root);

void						free_list(t_env *root);

int							edit_var_content(t_env *elem,
								char *cont, int booley);
int							edit_specific_var(t_env *root,
								char *lf, char *newc);

char						*line_env_interpret(char *inp, t_env *list);

void						derror(char *s1, char *s2, char *s3, int stats);

char						**splitter(char *inp);

int							ft_error(char *inp, int nerror);

int							terminit(t_env *env);

int							get_line(int rm, char **tf, t_histo **history);

int							k_arrows_sides(int lr, unsigned int cursor,
								char *scribe);
int							k_del(unsigned int cursor, char *scribe,
								char buffer[6]);
unsigned int				k_home_end(int kc, unsigned int cursor,
								char *scribe);

unsigned int				k_arrows_histo(int ud, unsigned int c,
								t_histo **histo, char **scribe);
void						register_history(char **to_fill, t_histo **history,
								char *scribe);
t_histo						*histo_init(void);
t_histo						*new_cmd_histo(int readm, t_histo **histo);

#endif
