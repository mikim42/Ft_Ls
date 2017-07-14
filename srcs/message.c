/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikim <mikim@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/01 20:27:26 by mikim             #+#    #+#             */
/*   Updated: 2017/06/02 23:17:17 by mikim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_nofile(char *s)
{
	ft_printf("ft_ls: %s: No such file or directory\n", s);
}

void	print_usage(char c)
{
	ft_printf("ls: illegal option -- %c\n", c);
	ft_printf("usage: ./ft_ls [-ACGLRUafglortu1] [file ...]\n");
	exit(2);
}
