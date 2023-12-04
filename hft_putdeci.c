/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hft_putdeci.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyao <jyao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 13:56:38 by jyao              #+#    #+#             */
/*   Updated: 2022/02/16 16:37:00 by jyao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static int	hft_count(t_fdata fdata, int deci, int *decicou)
{
	int		cou;
	char	issign;

	issign = ((deci < 0 || fdata.nplus || fdata.fplus) \
	);
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
	return (cou + issign);
}

static void	hft_writedeci(t_fdata fdata, int deci)
{
	char	rem;
	char	isintmin;

	if (fdata.isprec && !fdata.prec && !deci)
		return ;
	fdata.isprec = 0;
	isintmin = (deci == INT_MIN);
	if (isintmin)
	{
		rem = (deci % 10) * -1 + '0';
		deci += 1;
	}
	deci = deci * ((deci < 0) * -2 + 1);
	if (deci > 9)
		hft_writedeci(fdata, deci / 10);
	if (!isintmin)
		rem = deci % 10 + '0';
	write(1, &rem, 1);
}

void	hft_writesign(t_fdata fdata, int deci, char *wrote)
{
	if (!*wrote)
	{
		*wrote = 1;
		if (fdata.fplus && deci >= 0)
			write(1, "+", 1);
		else if (fdata.nplus && deci >= 0)
			write(1, " ", 1);
		else if (deci < 0)
			write(1, "-", 1);
	}
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

int	hft_putdeci(t_fdata fdata, int deci)
{
	char	wrote;
	int		cou;
	int		decicou;

	decicou = 0;
	wrote = 0;
	cou = hft_count(fdata, deci, &decicou);
	if (fdata.leftj)
	{
		hft_writesign(fdata, deci, &wrote);
		hft_writeprecwidth(fdata, decicou, cou, 1);
		hft_writedeci(fdata, deci);
		cou = hft_writeprecwidth(fdata, decicou, cou, 2);
	}
	else
	{
		if (!fdata.isprec && fdata.zeropd)
			hft_writesign(fdata, deci, &wrote);
		cou = hft_writeprecwidth(fdata, decicou, cou, 2);
		hft_writesign(fdata, deci, &wrote);
		hft_writeprecwidth(fdata, decicou, cou, 1);
		hft_writedeci(fdata, deci);
	}
	return (cou);
}
