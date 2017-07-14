/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikim <mikim@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/30 09:46:37 by mikim             #+#    #+#             */
/*   Updated: 2017/06/28 17:04:51 by mikim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	destroy_file(t_file *file)
{
	if (file)
	{
		free(file->name);
		destroy_file(file->next);
		free(file);
	}
}

void	print_ls(t_file *file, t_lsenv *e, char *path)
{
	if (file == NULL)
		return ;
	if (e->f.format == lsf_col)
		print_col(file, e);
	else if (e->f.format == lsf_one)
		print_one(file, e);
	else if (e->f.format == lsf_long)
		print_long(file, e, path);
}

void	ft_ls_recur(t_file *tmp, char *dir, t_lsenv *e)
{
	t_stat	status;
	char	*path;
	DIR		*d;

	path = ft_strcjoin(dir, '/', tmp->name);
	stat(path, &status);
	if (S_ISLNK(status.st_mode))
	{
		free(path);
		return ;
	}
	if ((d = opendir(path)) && strcmp(tmp->name, ".") != 0 &&
		strcmp(tmp->name, "..") != 0)
	{
		closedir(d);
		ft_printf("\n%s:\n", path);
		ft_ls(e, path);
	}
	else
	{
		d != 0 ? closedir(d) : 0;
		free(path);
	}
}

void	ft_ls(t_lsenv *e, char *dir)
{
	t_file	*file;
	t_file	*tmp;

	file = NULL;
	get_info(&file, dir, e);
	print_ls(file, e, dir);
	tmp = file;
	if (e->f.recur)
		while (tmp)
		{
			if (!S_ISLNK(tmp->stat.st_mode))
				ft_ls_recur(tmp, dir, e);
			tmp = tmp->next;
		}
	free(dir);
	destroy_file(file);
}

void	ft_ls_param(t_lsenv *e, char **av)
{
	t_file	*prm_dir;
	t_file	*prm_file;
	t_file	*tmp;

	prm_dir = NULL;
	prm_file = NULL;
	check_param(av, e);
	sep_param(av, &prm_dir, &prm_file, e);
	prm_file != NULL ? print_ls(prm_file, e, ft_strnew(1)) : 0;
	tmp = prm_dir;
	while (tmp)
	{
		(prm_dir && prm_dir->next) ? ft_printf("%s:\n", tmp->name) : 0;
		ft_ls(e, ft_strdup(tmp->name));
		tmp->next ? ft_printf("\n") : 0;
		tmp = tmp->next;
	}
	prm_dir != NULL ? destroy_file(prm_dir) : 0;
	prm_file != NULL ? destroy_file(prm_file) : 0;
}
