/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_float_handlers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ujyzene <ujyzene@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/27 00:12:42 by ujyzene           #+#    #+#             */
/*   Updated: 2019/08/12 15:49:18 by ujyzene          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

int	pf_float_handler(t_format *f, va_list args, t_pfs *out)
{
	char		*tmp;

	if (f->prec == -1)
		f->prec = 6;
	if (!!(f->mod & M_LDOUBLE))
		tmp = ft_lftoa(va_arg(args, long double), f->prec, f->sign);
	else
		tmp = !(f->opt & 2) ? ft_ftoa(va_arg(args, double), f->prec, f->sign) :
			ft_ftoe(va_arg(args, double), f->prec, f->sign);
	f->prec = -1;
	f->sign = SIGN(*tmp);
	if (f->pad == 32 && !f->sign)
		f->width -= pfs_write(out, " ", 1);
	if (!!(f->opt & 1))
		ft_chcase(&tmp, &ft_tolower);
	pfs_write(out, pf_fill(f, &tmp), -1);
	free(tmp);
	return (1);
}
