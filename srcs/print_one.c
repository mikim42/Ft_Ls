/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikim <mikim@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/11 16:49:49 by mikim             #+#    #+#             */
/*   Updated: 2017/06/26 17:34:00 by mikim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_one(t_file *file, t_lsenv *e)
{
	t_file	*tmp;

	tmp = file;
	while (tmp)
	{
		print_name(tmp, NULL, e);
		tmp = tmp->next;
	}
}
