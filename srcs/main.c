/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikim <mikim@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/30 09:35:52 by mikim             #+#    #+#             */
/*   Updated: 2017/06/26 23:46:01 by mikim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	init_lsflag(t_lsflag *f)
{
	f->format = 1;
	f->recur = 0;
	f->all = 0;
	f->color = 0;
	f->link = 0;
	f->rev = 0;
	f->sort = 0;
	f->gr = 0;
	f->usr = 0;
	f->time = 0;
}

void	init_lsenv(t_lsenv *e)
{
	struct winsize	w;

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	e->win = w.ws_col;
	e->max = 0;
	e->cnt = 0;
}

int		main(int ac, char **av)
{
	t_lsenv		e;
	int			i;

	i = 1;
	init_lsenv(&e);
	init_lsflag(&e.f);
	if (ac > 1)
	{
		if (av[1][0] == '-')
			i += get_lsflag(&e.f, av[1]);
		if (av[i] && !ft_strcmp(av[i], "--"))
			i++;
	}
	if (av[i] == NULL)
		ft_ls(&e, ft_strdup("."));
	else
		ft_ls_param(&e, av + i);
	return (0);
}
