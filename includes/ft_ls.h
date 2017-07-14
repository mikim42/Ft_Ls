/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikim <mikim@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/30 22:11:00 by mikim             #+#    #+#             */
/*   Updated: 2017/06/28 16:19:02 by mikim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <dirent.h>
# include <sys/stat.h>
# include <pwd.h>
# include <uuid/uuid.h>
# include <grp.h>
# include <sys/xattr.h>
# include <time.h>
# include <stdio.h>
# include <termios.h>
# include <sys/ioctl.h>
# include "libft.h"

typedef struct dirent	t_drt;
typedef struct stat		t_stat;

typedef enum		e_lsformat
{
	lsf_col = 1,
	lsf_one,
	lsf_long
}					t_lsf;

typedef struct		s_lsflag
{
	t_lsf			format;
	int				recur;
	int				all;
	int				color;
	int				link;
	int				rev;
	int				sort;
	int				gr;
	int				usr;
	int				time;
}					t_lsflag;

typedef	struct		s_file
{
	char			*name;
	int				nlen;
	int				total;
	t_stat			stat;
	struct s_file	*next;
}					t_file;

typedef struct		s_lsenv
{
	t_lsflag		f;
	int				win;
	int				max;
	int				cnt;
	int				total;
	int				llen;
	int				ulen;
	int				glen;
	int				slen;
}					t_lsenv;

/*
**					ft_ls
*/

void				ft_ls(t_lsenv *e, char *dir);
void				ft_ls_param(t_lsenv *e, char **av);
void				print_ls(t_file *file, t_lsenv *e, char *path);
void				ft_ls_recur(t_file *tmp, char *dir, t_lsenv *e);
void				destroy_file(t_file *file);
void				init_lsenv(t_lsenv *e);
void				init_lsflag(t_lsflag *f);

/*
**					get_flag
*/

int					get_lsflag(t_lsflag *f, char *av);
void				check_lsflag_up(t_lsflag *f, char c);
void				check_lsflag_low(t_lsflag *f, char c);

/*
**					get_param
*/

void				sep_param(char **av,
					t_file **dir, t_file **file, t_lsenv *e);
int					create_file_prm(t_file **new, char *file, t_lsenv *e);
void				check_param(char **av, t_lsenv *e);
void				sort_param(char **d);

/*
**					get_file_info
*/

void				get_info(t_file **head, char *dir, t_lsenv *e);
t_file				*create_file(t_drt *dp, char *path, t_lsenv *e);
int					check_all(t_drt *dp, t_lsenv *e);
void				add_file(t_file **head, t_file *new, t_lsenv *e);
void				sort_ascii(t_file **head, t_file *new);
void				sort_time(t_file **head, int t);
void				sort_rev(t_file **head);
int					cmp_time(t_file *f1, t_file *f2, int t);
int					check_exe(t_file *file);
char				*get_name(t_file *file, t_lsenv *e);

/*
**					print_col
*/

void				print_col(t_file *file, t_lsenv *e);
char				***get_colist(t_file *file, t_lsenv *e, int col);
char				***init_colist(t_lsenv *e, int col);
int					count_col_file(t_file *file, t_lsenv *e);

/*
**					print_long
*/

void				print_long(t_file *file, t_lsenv *e, char *path);
void				init_lenth(t_lsenv *e);
void				print_total(t_file *file, t_lsenv *e);
void				print_permission(t_file *file, char *path);
int					check_attr(char *name, t_file *file);
char				check_dirlink(char *name, t_file *file);
void				print_id(t_file *file, t_lsenv *e);
int					get_idlen(t_file *file, int var);
void				print_time(t_file *file, t_lsenv *e);
void				print_date(struct tm *tm);
int					check_time(struct tm file, struct tm curr);
void				print_name(t_file *file, char *path, t_lsenv *e);
void				print_link(t_file *file, char *path, t_lsenv *e);

/*
**					print_one
*/

void				print_one(t_file *file, t_lsenv *e);

/*
**					message
*/

void				print_usage(char c);
void				print_nofile(char *s);

#endif
