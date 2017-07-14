/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_file.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikim <mikim@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/02 23:27:26 by mikim             #+#    #+#             */
/*   Updated: 2017/06/28 16:27:00 by mikim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	sort_ascii(t_file **head, t_file *new)
{
	t_file *tmp;
	t_file *cur;

	cur = *head;
	if (ft_strcmp(cur->name, new->name) > 0)
	{
		*head = new;
		new->next = cur;
		return ;
	}
	while (cur)
	{
		tmp = cur;
		cur = cur->next;
		if (cur && ft_strcmp(cur->name, new->name) > 0)
		{
			new->next = cur;
			tmp->next = new;
			return ;
		}
	}
	tmp->next = new;
}

void	add_file(t_file **head, t_file *new, t_lsenv *e)
{
	t_file *list;

	if (new == NULL)
		return ;
	if (e->f.sort != 2)
		sort_ascii(head, new);
	else
	{
		list = *head;
		while (list->next)
			list = list->next;
		list->next = new;
	}
}

t_file	*create_file(t_drt *dp, char *path, t_lsenv *e)
{
	t_file	*new;
	char	*tmp;
	int		res;

	res = 0;
	new = (t_file*)malloc(sizeof(t_file));
	tmp = ft_strcjoin(path, '/', dp->d_name);
	if (e->f.link)
		res = stat(tmp, &new->stat);
	else
		res = lstat(tmp, &new->stat);
	free(tmp);
	if (res == -1)
	{
		free(new);
		return (NULL);
	}
	new->name = ft_strdup(dp->d_name);
	new->nlen = dp->d_namlen;
	new->next = NULL;
	return (new);
}

int		check_all(t_drt *dp, t_lsenv *e)
{
	if (e->f.all == 0)
	{
		if (dp->d_name[0] == '.')
			return (0);
		return (1);
	}
	else if (e->f.all == 1)
	{
		if (!ft_strcmp(dp->d_name, ".") || !ft_strcmp(dp->d_name, ".."))
			return (0);
		return (1);
	}
	return (1);
}

void	get_info(t_file **head, char *dir, t_lsenv *e)
{
	DIR		*d;
	t_drt	*dp;

	d = opendir(dir);
	while ((dp = readdir(d)))
	{
		if (check_all(dp, e))
		{
			*head == NULL ? *head = create_file(dp, dir, e) :
			add_file(head, create_file(dp, dir, e), e);
		}
	}
	closedir(d);
	if (*head == NULL)
		return ;
	if (e->f.sort == 1)
		sort_time(head, e->f.time);
	if (e->f.rev && (*head)->next != NULL)
		sort_rev(head);
}
