/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_id.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikim <mikim@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/24 14:03:36 by mikim             #+#    #+#             */
/*   Updated: 2017/06/28 16:11:32 by mikim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		get_idlen(t_file *file, int var)
{
	struct passwd	*usr;
	struct group	*gr;
	int				len;

	if (var)
	{
		usr = getpwuid(file->stat.st_uid);
		len = (int)ft_strlen(usr->pw_name);
		return (len);
	}
	else
	{
		gr = getgrgid(file->stat.st_gid);
		len = (int)ft_strlen(gr->gr_name);
		return (len);
	}
	return (0);
}

void	print_id(t_file *file, t_lsenv *e)
{
	struct passwd	*usr;
	struct group	*gr;

	if (!e->f.usr)
	{
		usr = getpwuid(file->stat.st_uid);
		ft_printf(" %*s", e->ulen, usr->pw_name);
	}
	if (!e->f.gr)
	{
		gr = getgrgid(file->stat.st_gid);
		ft_printf("  %*s", e->glen, gr->gr_name);
	}
}
