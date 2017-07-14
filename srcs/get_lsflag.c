/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_lsflag.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikim <mikim@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/01 18:45:36 by mikim             #+#    #+#             */
/*   Updated: 2017/06/28 17:20:17 by mikim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	check_lsflag_low(t_lsflag *f, char c)
{
	(c == 'o' || c == 'g') ? f->format = lsf_long : 0;
	if (c == 'a')
		f->all = 2;
	else if (c == 'f')
	{
		f->sort = 2;
		f->all = 2;
	}
	else if (c == 'l')
		f->format = lsf_long;
	else if (c == 'g')
		f->usr = 1;
	else if (c == 'o')
		f->gr = 1;
	else if (c == 'r')
		f->rev = 1;
	else if (c == 't')
		f->sort != 2 ? f->sort = 1 : 0;
	else if (c == 'u')
		f->time = 2;
	else
		print_usage(c);
}

void	check_lsflag_up(t_lsflag *f, char c)
{
	if (c == 'A')
		f->all != 2 ? f->all = 1 : 0;
	else if (c == 'C')
		f->format = lsf_col;
	else if (c == 'G')
		f->color = 1;
	else if (c == 'L')
		f->link = 1;
	else if (c == 'R')
		f->recur = 1;
	else if (c == 'U')
		f->time = 1;
	else if (c == '1')
		f->format = lsf_one;
	else
		print_usage(c);
}

int		get_lsflag(t_lsflag *f, char *av)
{
	int i;

	i = 0;
	if (!ft_strcmp(av, "--"))
		return (0);
	while (av[++i])
	{
		if (av[i] == '1' || (av[i] >= 'A' && av[i] <= 'U'))
			check_lsflag_up(f, av[i]);
		else if (av[i] >= 'a' && av[i] <= 'u')
			check_lsflag_low(f, av[i]);
		else
			print_usage(av[i]);
	}
	return (1);
}
