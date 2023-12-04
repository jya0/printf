/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hft_parsef.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyao <jyao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 18:38:20 by jyao              #+#    #+#             */
/*   Updated: 2022/02/18 18:21:59 by jyao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

//%[flags][width][.precision][length]specifier

static int	hft_flagass(const char c, t_fdata *fdata)
{
	if (!fdata->leftj)
		fdata->leftj = c == '-';
	if (!fdata->zeropd)
		fdata->zeropd = c == '0';
	if (!fdata->fplus)
		fdata->fplus = c == '+';
	if (!fdata->nplus)
		fdata->nplus = c == ' ';
	if (!fdata->pfix)
		fdata->pfix = c == '#';
	return (c == '-' || c == '0' || c == '+' || \
	c == ' ' || c == '#');
}

static int	hft_whass(const char c, t_fdata *fdata)
{
	if (c >= '0' && c <= '9')
	{
		fdata->width = fdata->width * 10 + (c - '0');
		return (1);
	}
	return (0);
}

static int	hft_prass(const char c, t_fdata *fdata)
{
	if (c >= '0' && c <= '9')
	{
		fdata->prec = fdata->prec * 10 + (c - '0');
		return (1);
	}
	return (0);
}

static int	hft_spass(const char c, t_fdata *fdata)
{
	if (c == 'c' || c == 's' || c == 'p' || c == 'd' || \
	c == 'i' || c == 'u' || c == 'x' || c == 'X' || c == '%')
	{
		fdata->spec = c;
		return (1);
	}
	return (0);
}

t_fdata	hft_parsef(const char **format)
{
	t_fdata	fdata;

	fdata = (t_fdata){0};
	while (hft_flagass(**format, &fdata))
		(*format)++;
	if (fdata.leftj)
		fdata.zeropd = 0;
	while (hft_whass(**format, &fdata))
		(*format)++;
	if (**format == '.')
	{
		fdata.isprec = 1;
		fdata.zeropd = 0;
		if (*(*format + 1))
			(*format)++;
		while (hft_prass(**format, &fdata))
			(*format)++;
	}
	hft_spass(**format, &fdata);
	return (fdata);
}
