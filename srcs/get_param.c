/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_param.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikim <mikim@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/01 19:17:50 by mikim             #+#    #+#             */
/*   Updated: 2017/06/28 17:11:59 by mikim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	sort_param(char **d)
{
	char	*tmp;
	int		i;

	i = -1;
	while (d[++i + 1])
	{
		if (ft_strcmp(d[i], d[i + 1]) > 0)
		{
			tmp = d[i + 1];
			d[i + 1] = d[i];
			d[i] = tmp;
			i = -1;
		}
	}
}

void	check_param(char **av, t_lsenv *e)
{
	t_stat	status;
	int		len;
	int		i;

	e->f.sort != 2 ? sort_param(av) : 0;
	i = -1;
	while (av[++i])
	{
		if (stat(av[i], &status) == -1)
		{
			print_nofile(av[i]);
			ft_strclr(av[i]);
		}
		len = (int)ft_strlen(av[i]);
		if (av[i][len - 1] == '/')
			av[i][len - 1] = '\0';
	}
}

int		create_file_prm(t_file **new, char *file, t_lsenv *e)
{
	DIR	*d;
	int	res;

	*new = (t_file*)malloc(sizeof(t_file));
	if (e->f.link)
		res = stat(file, &(*new)->stat);
	else
		res = lstat(file, &(*new)->stat);
	if (res == -1)
	{
		free(*new);
		return (-1);
	}
	(*new)->name = ft_strdup(file);
	(*new)->nlen = (int)ft_strlen(file);
	(*new)->next = NULL;
	if ((d = opendir(file)))
	{
		closedir(d);
		return (S_ISLNK((*new)->stat.st_mode) == 1 ? 0 : 1);
	}
	d != 0 ? closedir(d) : 0;
	return (0);
}

void	sep_param(char **av, t_file **dir, t_file **file, t_lsenv *e)
{
	t_file	*new;
	int		i;
	int		res;

	i = -1;
	new = NULL;
	while (av[++i])
	{
		av[i][0] != '\0' ? res = create_file_prm(&new, av[i], e) : 0;
		if (av[i][0] != '\0' && res == 1)
			*dir == NULL ? *dir = new : add_file(dir, new, e);
		else if (av[i][0] != '\0' && res == 0)
			*file == NULL ? *file = new : add_file(file, new, e);
	}
	if (e->f.sort == 1)
	{
		*dir != NULL ? sort_time(dir, e->f.time) : 0;
		*file != NULL ? sort_time(file, e->f.time) : 0;
	}
	if (e->f.rev)
	{
		(*dir != NULL && (*dir)->next != NULL) ? sort_rev(dir) : 0;
		(*file != NULL && (*file)->next != NULL) ? sort_rev(file) : 0;
	}
}
