/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hft_putchar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyao <jyao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 14:16:20 by jyao              #+#    #+#             */
/*   Updated: 2022/02/08 17:32:50 by jyao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

//%[flags][width][.precision][length]specifier

int	hft_putchar(t_fdata fdata, const char c)
{
	int	cou;

	cou = 0;
	if (fdata.leftj)
	{
		write(1, &c, 1);
		while (fdata.width > ++cou)
			write(1, " ", 1);
	}
	else
	{
		while (fdata.width > ++cou)
		{
			if (fdata.zeropd)
				write(1, "0", 1);
			else
				write(1, " ", 1);
		}
		write(1, &c, 1);
	}
	return (cou);
}
