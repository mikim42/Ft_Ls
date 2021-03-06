/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_upcase.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikim <mikim@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/20 23:40:58 by mikim             #+#    #+#             */
/*   Updated: 2017/04/30 09:14:09 by mikim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_upcase(char *s)
{
	int i;

	i = -1;
	while (s[++i])
	{
		if (s[i] >= 97 && s[i] <= 122)
			s[i] += -32;
	}
}
