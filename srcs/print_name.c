/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_name.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikim <mikim@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/24 14:22:16 by mikim             #+#    #+#             */
/*   Updated: 2017/06/27 18:13:28 by mikim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		check_exe(t_file *file)
{
	if (S_IXUSR & file->stat.st_mode ||
		S_IXGRP & file->stat.st_mode ||
		S_IXOTH & file->stat.st_mode)
		return (1);
	return (0);
}

void	print_link(t_file *file, char *path, t_lsenv *e)
{
	t_stat	status;
	char	*link;
	char	*tmp;

	if (e->f.format == lsf_long)
	{
		tmp = (path[0] == '\0' ?
		ft_strdup(file->name) : ft_strcjoin(path, '/', file->name));
		lstat(tmp, &status);
		link = (char*)malloc(sizeof(char) * status.st_size + 1);
		readlink(tmp, link, status.st_size + 1);
		link[status.st_size] = '\0';
		if (e->f.color)
			ft_printf("{MGT}%s{OFF} -> %s\n", file->name, link);
		else
			ft_printf("%s -> %s\n", file->name, link);
		free(tmp);
		free(link);
	}
	else
		ft_printf("%s\n", file->name);
}

char	*get_name(t_file *file, t_lsenv *e)
{
	char	*tmp[2];

	if (!e->f.color)
		return (ft_strdup(file->name));
	if (S_ISDIR(file->stat.st_mode))
		tmp[0] = ft_strjoin("\x1b[34m", file->name);
	else if (S_ISLNK(file->stat.st_mode))
		tmp[0] = ft_strjoin("\x1b[35m", file->name);
	else if (S_ISSOCK(file->stat.st_mode))
		tmp[0] = ft_strjoin("\x1b[32m", file->name);
	else if (S_ISFIFO(file->stat.st_mode))
		tmp[0] = ft_strjoin("\x1b[30m", file->name);
	else if (S_ISREG(file->stat.st_mode) && check_exe(file))
		tmp[0] = ft_strjoin("\x1b[31m", file->name);
	else if (S_ISBLK(file->stat.st_mode))
		tmp[0] = ft_strjoin("\x1b[36m", file->name);
	else if (S_ISCHR(file->stat.st_mode))
		tmp[0] = ft_strjoin("\x1b[30m", file->name);
	else
		tmp[0] = ft_strjoin("\x1b[00m", file->name);
	tmp[1] = ft_strjoin(tmp[0], "\x1b[0m");
	free(tmp[0]);
	return (tmp[1]);
}

void	print_name(t_file *file, char *path, t_lsenv *e)
{
	if (S_ISLNK(file->stat.st_mode))
		return (print_link(file, path, e));
	if (!e->f.color)
		ft_printf("%s\n", file->name);
	else
	{
		if (S_ISDIR(file->stat.st_mode))
			ft_printf("{BLU}%s{OFF}\n", file->name);
		else if (S_ISSOCK(file->stat.st_mode))
			ft_printf("{GRN}%s{OFF}\n", file->name);
		else if (S_ISFIFO(file->stat.st_mode))
			ft_printf("{BLK}%s{OFF}\n", file->name);
		else if (S_ISREG(file->stat.st_mode) && check_exe(file))
			ft_printf("{RED}%s{OFF}\n", file->name);
		else if (S_ISBLK(file->stat.st_mode))
			ft_printf("{CYN}%s{OFF}\n", file->name);
		else if (S_ISCHR(file->stat.st_mode))
			ft_printf("{BLK}%s{OFF}\n", file->name);
		else
			ft_printf("%s\n", file->name);
	}
}
