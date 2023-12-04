/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyao <jyao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 15:28:18 by jyao              #+#    #+#             */
/*   Updated: 2022/02/18 15:00:17 by jyao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static int	hft_printf(const char **format, va_list agpt)
{
	t_fdata	fdata;

	if (*(*format + 1))
		(*format)++;
	else
		return (0);
	fdata = hft_parsef(format);
	if (fdata.spec == '%')
		return (hft_putchar(fdata, '%'));
	if (fdata.spec == 'c')
		return (hft_putchar(fdata, va_arg(agpt, int)));
	if (fdata.spec == 's')
		return (hft_putstr(fdata, va_arg(agpt, char *)));
	if (fdata.spec == 'd' || fdata.spec == 'i')
		return (hft_putdeci(fdata, va_arg(agpt, int)));
	if (fdata.spec == 'u')
		return (hft_putudeci(fdata, va_arg(agpt, unsigned int)));
	if (fdata.spec == 'x' || fdata.spec == 'X' || fdata.spec == 'p')
		return (hft_putlhex(fdata, va_arg(agpt, size_t)));
	return (0);
}

int	ft_printf(const char *format, ...)
{
	va_list	agpt;
	int		cou;

	va_start(agpt, format);
	cou = 0;
	while (*format)
	{
		if (*format == '%')
			cou += hft_printf(&format, agpt);
		else
		{
			write(1, format, 1);
			cou++;
		}
		format++;
	}
	va_end(agpt);
	return (cou);
}
