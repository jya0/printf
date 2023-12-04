/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hft_writehexpfix.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyao <jyao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 19:17:13 by jyao              #+#    #+#             */
/*   Updated: 2022/02/16 16:26:43 by jyao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void	hft_writehexpfix(t_fdata fdata, size_t hex, char *hexset, char *wrote)
{
	if (fdata.spec != 'p')
		hex = (unsigned)hex;
	if (!*wrote && ((fdata.pfix && hex) || fdata.spec == 'p'))
	{
		*wrote = 1;
		write(1, "0", 1);
		write(1, &hexset[16], 1);
	}
}
