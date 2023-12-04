/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hft_putudeci.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyao <jyao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 17:39:54 by jyao              #+#    #+#             */
/*   Updated: 2022/02/16 16:38:32 by jyao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static int	hft_count(t_fdata fdata, unsigned int deci, int *decicou)
{
	int		cou;

	cou = 0;
	if (fdata.isprec && !fdata.prec && deci == 0)
		cou = 0;
	else if (deci == 0)
		cou = 1;
	while (deci)
	{
		deci /= 10;
		cou++;
	}
	*decicou = cou;
	if (fdata.isprec && cou < fdata.prec)
		cou = fdata.prec;
	return (cou);
}

static void	hft_writedeci(t_fdata fdata, unsigned int deci)
{
	char	rem;

	if (fdata.isprec && !fdata.prec && !deci)
		return ;
	fdata.isprec = 0;
	if (deci > 9)
		hft_writedeci(fdata, deci / 10);
	rem = deci % 10 + '0';
	write(1, &rem, 1);
}

static int	hft_writeprecwidth(t_fdata fdata, int decicou, int cou, int option)
{
	int	i;

	i = 0;
	if (option == 1)
	{
		while (fdata.isprec && decicou < fdata.prec)
		{
			write(1, "0", 1);
			decicou++;
		}
	}
	else if (option == 2)
	{
		while (cou + i < fdata.width)
		{
			if (fdata.zeropd)
				write(1, "0", 1);
			else
				write(1, " ", 1);
			i++;
		}
	}
	return (cou + i);
}

int	hft_putudeci(t_fdata fdata, unsigned int deci)
{
	int		cou;
	int		decicou;

	decicou = 0;
	cou = hft_count(fdata, deci, &decicou);
	if (fdata.leftj)
	{
		hft_writeprecwidth(fdata, decicou, cou, 1);
		hft_writedeci(fdata, deci);
		cou = hft_writeprecwidth(fdata, decicou, cou, 2);
	}
	else
	{
		cou = hft_writeprecwidth(fdata, decicou, cou, 2);
		hft_writeprecwidth(fdata, decicou, cou, 1);
		hft_writedeci(fdata, deci);
	}
	return (cou);
}
