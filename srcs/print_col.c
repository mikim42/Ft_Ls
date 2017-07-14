/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_col.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikim <mikim@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/11 16:49:49 by mikim             #+#    #+#             */
/*   Updated: 2017/06/26 16:52:14 by mikim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		count_col_file(t_file *file, t_lsenv *e)
{
	t_file	*tmp;
	int		cnt;
	int		len;
	int		i;

	cnt = 0;
	len = 0;
	tmp = file;
	while (tmp)
	{
		cnt++;
		len = (len < tmp->nlen ? tmp->nlen : len);
		tmp = tmp->next;
	}
	e->max = ((len / 4) + 1) * 4;
	e->cnt = cnt;
	i = 0;
	while (i++ > -1)
		if ((e->cnt / i) * e->max < e->win)
			break ;
	return (e->cnt / i);
}

char	***init_colist(t_lsenv *e, int col)
{
	char	***cl;
	int		res;
	int		i;
	int		j;

	res = (e->cnt / col) + (e->cnt % col > 0);
	cl = (char***)malloc(sizeof(char**) * (res + 1));
	cl[res] = NULL;
	i = -1;
	res = (e->cnt / col) + (e->cnt % col > 0);
	while (++i < res)
	{
		cl[i] = (char**)malloc(sizeof(char*) * (col + 1));
		j = -1;
		while (++j <= col)
			cl[i][j] = NULL;
	}
	return (cl);
}

char	***get_colist(t_file *file, t_lsenv *e, int col)
{
	char	***cl;
	t_file	*tmp;
	int		i;
	int		j;

	cl = init_colist(e, col);
	tmp = file;
	i = 0;
	j = 0;
	while (tmp)
	{
		cl[i++][j] = get_name(tmp, e);
		if (cl[i] == NULL)
		{
			i = 0;
			j++;
		}
		tmp = tmp->next;
	}
	return (cl);
}

void	print_col(t_file *file, t_lsenv *e)
{
	char	***s;
	int		col;
	int		i;
	int		j;

	col = count_col_file(file, e);
	s = get_colist(file, e, col);
	i = -1;
	while (s[++i])
	{
		j = -1;
		while (s[i][++j])
		{
			if (s[i][j + 1])
				ft_printf("%-*s", e->max + (e->f.color ? 8 : 0), s[i][j]);
			else
				ft_printf("%-*s\n", e->max + (e->f.color ? 8 : 0), s[i][j]);
			free(s[i][j]);
		}
		free(s[i]);
	}
}
