/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyao <jyao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 17:31:31 by jyao              #+#    #+#             */
/*   Updated: 2022/02/16 16:23:57 by jyao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTPRINTF_H
# define LIBFTPRINTF_H

# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

typedef struct s_fdata{
	unsigned char	leftj;
	unsigned char	zeropd;
	unsigned char	fplus;
	unsigned char	nplus;
	unsigned char	pfix;
	int				width;
	unsigned char	isprec;
	int				prec;
	unsigned char	spec;
}	t_fdata;

int		ft_printf(const char *format, ...);
t_fdata	hft_parsef(const char **format);

int		hft_putchar(t_fdata fdata, const char c);

int		hft_putstr(t_fdata fdata, const char *str);

int		hft_putdeci(t_fdata fdata, int deci);

int		hft_putudeci(t_fdata fdata, unsigned int deci);

int		hft_putlhex(t_fdata fdata, size_t hex);
void	hft_writehexpfix(t_fdata fdata, size_t hex, char *hexset, char *wrote);

#endif