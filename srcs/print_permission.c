/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_permission.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikim <mikim@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/22 15:29:23 by mikim             #+#    #+#             */
/*   Updated: 2017/06/27 21:26:57 by mikim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char	check_dirlink(char *name, t_file *file)
{
	DIR		*d;
	char	res;

	d = NULL;
	if (S_ISLNK(file->stat.st_mode))
		res = 'l';
	else if ((d = opendir(name)) ||
		(!ft_strcmp(file->name, ".") || !ft_strcmp(file->name, "..")))
		res = 'd';
	else
		res = '-';
	d != 0 ? closedir(d) : 0;
	free(name);
	return (res);
}

int		check_attr(char *name, t_file *file)
{
	int		res;
	t_stat	status;

	res = 0;
	if (!ft_strcmp(file->name, ".") || !ft_strcmp(file->name, ".."))
		return (0);
	if (S_ISLNK(file->stat.st_mode))
	{
		lstat(name, &status);
		if (listxattr(name, NULL, 0, XATTR_NOFOLLOW) > 0 ||
			listxattr(name, NULL, 0, XATTR_SHOWCOMPRESSION) > 0)
			res = 1;
	}
	else if (listxattr(name, NULL, 0, XATTR_NOFOLLOW) > 0 ||
		listxattr(name, NULL, 0, XATTR_SHOWCOMPRESSION) > 0)
		res = 1;
	free(name);
	return (res);
}

void	print_permission(t_file *file, char *path)
{
	char	s[12];

	s[0] = check_dirlink(ft_strcjoin(path, '/', file->name), file);
	s[1] = S_IRUSR & file->stat.st_mode ? 'r' : '-';
	s[2] = S_IWUSR & file->stat.st_mode ? 'w' : '-';
	s[3] = S_IXUSR & file->stat.st_mode ? 'x' : '-';
	s[4] = S_IRGRP & file->stat.st_mode ? 'r' : '-';
	s[5] = S_IWGRP & file->stat.st_mode ? 'w' : '-';
	s[6] = S_IXGRP & file->stat.st_mode ? 'x' : '-';
	s[7] = S_IROTH & file->stat.st_mode ? 'r' : '-';
	s[8] = S_IWOTH & file->stat.st_mode ? 'w' : '-';
	s[9] = S_IXOTH & file->stat.st_mode ? 'x' : '-';
	s[10] = check_attr(ft_strcjoin(path, '/', file->name), file) ? '@' : ' ';
	s[11] = '\0';
	ft_printf("%s", s);
}
