/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hft_putlhex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyao <jyao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 18:14:40 by jyao              #+#    #+#             */
/*   Updated: 2022/02/16 16:38:44 by jyao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static void	hft_hexset(t_fdata fdata, char *hexset)
{
	char	*og;

	og = "0123456789abcdefx";
	while (*og)
	{
		if (fdata.spec == 'X' && (*og >= 'a' && *og <= 'z'))
			*hexset = *og + 'A' - 'a';
		else
			*hexset = *og;
		hexset++;
		og++;
	}
}

static int	hft_count(t_fdata fdata, size_t hex, int *hexcou)
{
	int		cou;
	int		pfix;

	if (fdata.spec != 'p')
		hex = (unsigned)hex;
	cou = 0;
	if (fdata.isprec && !fdata.prec && hex == 0)
		cou = 0;
	else if (hex == 0)
		cou = 1;
	pfix = 0;
	if ((fdata.pfix && hex) || fdata.spec == 'p')
		pfix = 2;
	while (hex)
	{
		hex /= 16;
		cou++;
	}
	*hexcou = cou;
	if (fdata.isprec && cou < fdata.prec)
		cou = fdata.prec;
	return (cou + pfix);
}

static void	hft_writehex(t_fdata fdata, size_t hex, char *hexset, int hexcou)
{
	if (fdata.isprec && !fdata.prec && !hex)
		return ;
	fdata.isprec = 0;
	if (!hexcou)
		return ;
	if (hex > 15)
		hft_writehex(fdata, hex / 16, hexset, --hexcou);
	write(1, &hexset[hex % 16], 1);
}

static int	hft_writeprecwidth(t_fdata fdata, int hexcou, int cou, int option)
{
	int	i;

	i = 0;
	if (option == 1)
	{
		while (fdata.isprec && hexcou < fdata.prec)
		{
			write(1, "0", 1);
			hexcou++;
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

int	hft_putlhex(t_fdata fdata, size_t hex)
{
	char	hexset[17];
	int		cou;
	int		hexcou;
	char	wrote;

	hft_hexset(fdata, hexset);
	wrote = 0;
	cou = hft_count(fdata, hex, &hexcou);
	if (fdata.leftj)
	{
		hft_writehexpfix(fdata, hex, hexset, &wrote);
		hft_writeprecwidth(fdata, hexcou, cou, 1);
		hft_writehex(fdata, hex, hexset, hexcou);
		cou = hft_writeprecwidth(fdata, hexcou, cou, 2);
	}
	else
	{
		if (!fdata.isprec && fdata.zeropd)
			hft_writehexpfix(fdata, hex, hexset, &wrote);
		cou = hft_writeprecwidth(fdata, hexcou, cou, 2);
		hft_writehexpfix(fdata, hex, hexset, &wrote);
		hft_writeprecwidth(fdata, hexcou, cou, 1);
		hft_writehex(fdata, hex, hexset, hexcou);
	}
	return (cou);
}
