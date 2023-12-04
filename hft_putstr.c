/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hft_putstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyao <jyao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 17:36:37 by jyao              #+#    #+#             */
/*   Updated: 2022/02/13 19:09:55 by jyao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static int	hft_oputstr(t_fdata fdata, const char *str, char output)
{
	int	i;

	i = 0;
	if (fdata.isprec)
	{
		while (str[i] && i < fdata.prec)
		{
			if (output)
				write(1, &str[i], 1);
			i++;
		}
	}
	else
	{
		while (str[i])
		{
			if (output)
				write(1, &str[i], 1);
			i++;
		}
	}
	return (i);
}

static int	hft_fillwidth_str(t_fdata fdata, int cou)
{
	while (fdata.width > cou)
	{
		if (fdata.zeropd)
			write(1, "0", 1);
		else
			write(1, " ", 1);
		cou++;
	}
	return (cou);
}

int	hft_putstr(t_fdata fdata, const char *str)
{
	int	cou;

	if (!str)
		return (hft_putstr(fdata, "(null)"));
	if (fdata.leftj)
	{
		cou = hft_oputstr(fdata, str, 1);
		while (fdata.width > cou)
		{
			write(1, " ", 1);
			cou++;
		}
	}
	else
	{
		cou = hft_oputstr(fdata, str, 0);
		cou = hft_fillwidth_str(fdata, cou);
		hft_oputstr(fdata, str, 1);
	}
	return (cou);
}
