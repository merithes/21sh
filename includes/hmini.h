/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hmini.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jamerlin <jamerlin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/26 21:25:52 by vboivin           #+#    #+#             */
/*   Updated: 2018/01/30 15:49:48 by vboivin          ###   ########.fr       */
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
** =============================================================================
*/

# define EXIT 55
# define MONE (1)
# define MTWO (1 << 1)
# define MFOU (1 << 2)
# define MPL MAXPATHLEN

# define LEFT 1
# define RIGHT 0

# define MAX_HISTO 25

# define NONE 0
# define PIPE 1 << 1
# define SEPA 1 << 2
# define OR 1 << 3
# define AND 1 << 4
# define BCKG 1 << 5

# define F_NONE 0
# define F_MAIN_ONLY 1
# define F_ALL 1 << 1

/*
** /!\SYSTEM DEPENDANT /!\
** =============================================================================
*/

/*
** MACROS
** =============================================================================
*/

# define N_ENV "Environment received empty. Creating a new one.\n"
# define DEF_PROMPT "[\\s]\\u> "
# define DEF_PATH "/bin:/usr/bin:/usr/local/bin:/sbin:/usr/sbin"

# define NSFOD " No such file or directory\n"
# define NEOB " File doesn't exist or isn't a binary"
# define NSC " No such command\n"
# define BACKMX "4294967295"
# define MAF "Memory Allocation Failed.\n"
# define SHNAME "21sh: "

/*
** Error related defined values
** =============================================================================
*/

# define ERRP1 "21sh: Parse error near '"
# define ERRP2_1 "21sh: Unexpected token '"
# define ERRP2_2 "' After '"
# define ERRP3 "21sh: Expected file name after token '"
# define ERRP4 "21sh: Invalid redirection token '"

# define ERR_1 1
# define ERR_2 2
# define ERR_3 3
# define ERR_4 4

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
}							t_histo;

typedef struct termios		t_ermios;

/*
** STRUCT T_LISTC
** sep_type = type of tokken (pipe, 'or' etc. as defined in the DEFINED VALUES)
** cont = equivalent to "char **argv", processed infos.
** redir[3] =	0 = fd redir
** 				1 = type of redir (0 "<" / 1 ">" / 2 "<<" / 3 ">>")
** 				2 = fd receptor
** *file = file to redirect to
*/

typedef struct				s_redir
{
	int						redir[3];
	char					*file;
	struct s_redir			*next;
}							t_redir;

typedef struct				s_list_complete
{
	int						sep_type;
	char					**cont;
	int						nb_arg;
	t_redir					*redirs;
	struct s_list_complete	*prev;
	struct s_list_complete	*next;
}							t_listc;

/*
** GLOBALS
** =============================================================================
*/

t_ermios					g_termcap_21sh[2];
t_env						*g_backup_env;

/*
** DECLARATIONS
** =============================================================================
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
void						free_rec_listc(t_listc *inp, int free_cont);

int							edit_var_content(t_env *elem,
								char *cont, int booley);
int							edit_specific_var(t_env *root,
								char *lf, char *newc);

char						*line_env_interpret(char *inp, t_env *list);

void						derror(char *s1, char *s2, char *s3, int stats);

char						**splitter(char *inp);
char						**splitter_alt(char *inp);

int							ft_error(char *inp, int nerror);

int							terminit(t_env *env);

int							get_line(int rm, char **tf, t_histo **history);

int							k_arrows_sides(int lr, unsigned int cursor,
								char *scribe);
int							k_del(unsigned int cursor, char *scribe,
								char buffer[6]);
unsigned int				k_home_end(int kc, unsigned int cursor,
								char *scribe);
unsigned int				k_arrows_skipwd(char *scribe, unsigned int c,
								int left);

unsigned int				k_arrows_histo(int ud, unsigned int c,
								t_histo **histo, char **scribe);
void						register_history(char **to_fill, t_histo **history,
								char *scribe);
t_histo						*histo_init(void);
t_histo						*new_cmd_histo(int readm, t_histo **histo);

void						move_forw(int i);
void						move_back(int i);

void						clear_scrn(char *cli, unsigned int cursor_pos);

void						exec_cli_lst(char *cli, t_env *env);
void						exec_cli(char *cli, t_listc *full_details,
								t_env *env);
void						grow_ast(char *i, t_env *e);
t_listc						*cut_string_delimiters(char **inp);
void						exec_lst(t_listc *inp, t_env *env);

t_listc						*create_chain_link(t_listc *prevv);

char						**set_link(t_listc *link, char **cli_cut);

int							detect_delimiters(char **inp);
char						**detect_bad_delimiters(char **inp);

int							contains_delims(char *inp);

t_list						*convert_inp_lst(char **inp);
int							lex_splitted(char **inp);

void    test(t_listc *cmd);
void    redirect(t_listc *cmd);
#endif
