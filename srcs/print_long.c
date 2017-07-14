/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_long.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikim <mikim@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/11 16:49:49 by mikim             #+#    #+#             */
/*   Updated: 2017/06/28 15:49:05 by mikim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	init_lenth(t_lsenv *e)
{
	e->total = 0;
	e->llen = 0;
	e->ulen = 0;
	e->glen = 0;
	e->slen = 0;
}

void	print_total(t_file *file, t_lsenv *e)
{
	t_file	*tmp;
	int		ulen;
	int		glen;
	int		slen;
	int		llen;

	init_lenth(e);
	tmp = file;
	while (tmp)
	{
		e->total += tmp->stat.st_blocks;
		llen = (int)ft_intlen(tmp->stat.st_nlink);
		e->llen < llen ? e->llen = llen : 0;
		ulen = get_idlen(tmp, 1);
		e->ulen < ulen ? e->ulen = ulen : 0;
		glen = get_idlen(tmp, 0);
		e->glen < glen ? e->glen = glen : 0;
		e->slen < (slen = ft_intlen((int)tmp->stat.st_size)) ?
		e->slen = slen : 0;
		tmp = tmp->next;
	}
	ft_printf("total %d\n", e->total);
}

void	print_long(t_file *file, t_lsenv *e, char *path)
{
	t_file		*tmp;

	print_total(file, e);
	tmp = file;
	while (tmp)
	{
		print_permission(tmp, path);
		ft_printf(" %*d", e->llen, tmp->stat.st_nlink);
		print_id(file, e);
		ft_printf("  %*d", e->slen, (int)tmp->stat.st_size);
		print_time(tmp, e);
		print_name(tmp, path, e);
		tmp = tmp->next;
	}
}
