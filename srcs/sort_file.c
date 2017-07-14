/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikim <mikim@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/03 00:50:49 by mikim             #+#    #+#             */
/*   Updated: 2017/06/26 21:06:14 by mikim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		cmp_time(t_file *f1, t_file *f2, int t)
{
	if (t == 0)
		return (f1->stat.st_mtimespec.tv_sec < f2->stat.st_mtimespec.tv_sec);
	else if (t == 1)
		return (f1->stat.st_ctimespec.tv_sec < f2->stat.st_ctimespec.tv_sec);
	return (f1->stat.st_atimespec.tv_sec < f2->stat.st_atimespec.tv_sec);
}

void	sort_time(t_file **head, int t)
{
	t_file *sort[3];

	sort[0] = *head;
	sort[1] = sort[0]->next;
	if (sort[1] && cmp_time(sort[0], sort[1], t))
	{
		sort[0]->next = sort[1]->next;
		sort[1]->next = sort[0];
		*head = sort[1];
		return (sort_time(head, t));
	}
	while (sort[1])
	{
		sort[2] = sort[1]->next;
		if (sort[2] && cmp_time(sort[1], sort[2], t))
		{
			sort[1]->next = sort[2]->next;
			sort[2]->next = sort[1];
			sort[0]->next = sort[2];
			return (sort_time(head, t));
		}
		sort[0] = sort[1];
		sort[1] = sort[0]->next;
	}
}

void	sort_rev(t_file **head)
{
	t_file	*sort[3];

	if ((*head)->next->next == NULL)
	{
		sort[0] = (*head)->next;
		*head = (*head)->next;
		(*head)->next = sort[0];
		(*head)->next = NULL;
		return ;
	}
	sort[0] = (*head)->next->next;
	sort[1] = (*head)->next;
	sort[2] = *head;
	while (sort[0]->next)
	{
		sort[1]->next = sort[2];
		sort[2] = sort[1];
		sort[1] = sort[0];
		sort[0] = sort[0]->next;
	}
	sort[1]->next = sort[2];
	sort[0]->next = sort[1];
	(*head)->next = NULL;
	(*head) = sort[0];
}
