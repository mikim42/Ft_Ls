/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_time.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikim <mikim@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/22 16:21:36 by mikim             #+#    #+#             */
/*   Updated: 2017/06/26 16:49:25 by mikim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		check_time(struct tm file, struct tm curr)
{
	if (file.tm_year + 1 < curr.tm_year)
		return (0);
	if (file.tm_year == curr.tm_year)
	{
		if (file.tm_mon + 6 < curr.tm_mon)
			return (0);
		if (file.tm_mon + 6 == curr.tm_mon &&
			file.tm_mday < curr.tm_mday)
			return (0);
	}
	else if (file.tm_year < curr.tm_year)
	{
		if (file.tm_mon + 6 < curr.tm_mon + 12)
			return (0);
		if (file.tm_mon + 6 == curr.tm_mon + 12 &&
		file.tm_mday < curr.tm_mday)
			return (0);
	}
	return (1);
}

void	print_date(struct tm *tm)
{
	if (tm->tm_mon == 0)
		ft_printf(" Jan %2d", tm->tm_mday);
	else if (tm->tm_mon == 1)
		ft_printf(" Feb %2d", tm->tm_mday);
	else if (tm->tm_mon == 2)
		ft_printf(" Mar %2d", tm->tm_mday);
	else if (tm->tm_mon == 3)
		ft_printf(" Apr %2d", tm->tm_mday);
	else if (tm->tm_mon == 4)
		ft_printf(" May %2d", tm->tm_mday);
	else if (tm->tm_mon == 5)
		ft_printf(" Jun %2d", tm->tm_mday);
	else if (tm->tm_mon == 6)
		ft_printf(" Jul %2d", tm->tm_mday);
	else if (tm->tm_mon == 7)
		ft_printf(" Aug %2d", tm->tm_mday);
	else if (tm->tm_mon == 8)
		ft_printf(" Sep %2d", tm->tm_mday);
	else if (tm->tm_mon == 9)
		ft_printf(" Oct %2d", tm->tm_mday);
	else if (tm->tm_mon == 10)
		ft_printf(" Nov %2d", tm->tm_mday);
	else if (tm->tm_mon == 11)
		ft_printf(" Dec %2d", tm->tm_mday);
}

void	print_time(t_file *file, t_lsenv *e)
{
	struct tm	*tm;
	struct tm	cf_tm[2];
	time_t		t[2];

	t[0] = time(NULL);
	tm = localtime(&t[0]);
	cf_tm[0] = *tm;
	t[1] = 0;
	if (e->f.time == 0)
		t[1] = file->stat.st_mtimespec.tv_sec;
	else if (e->f.time == 1)
		t[1] = file->stat.st_ctimespec.tv_sec;
	else if (e->f.time == 2)
		t[1] = file->stat.st_atimespec.tv_sec;
	tm = localtime(&t[1]);
	cf_tm[1] = *tm;
	print_date(&cf_tm[1]);
	if (t[1] <= t[0] && check_time(cf_tm[1], cf_tm[0]))
		ft_printf(" %02d:%02d ", cf_tm[1].tm_hour, cf_tm[1].tm_min);
	else
		ft_printf("  %-4d ", cf_tm[1].tm_year + 1900);
}
