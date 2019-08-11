/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_float_handlers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ujyzene <ujyzene@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/27 00:12:42 by ujyzene           #+#    #+#             */
/*   Updated: 2019/08/11 05:59:22 by ujyzene          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

int	pf_float_handler(t_format *f, va_list args, t_pfs *out)
{
	char		*tmp;
	long double	n;

	if (!!(f->mod & M_LDOUBLE))
		n = va_arg(args, long double);
	else
		n = va_arg(args, double);
	if (f->prec == -1)
		f->prec = 6;
	tmp = !(f->opt & 2) ? !!(f->mod & M_LDOUBLE) ?
		ft_lftoa(n, f->prec, f->sign) : ft_ftoa(n, f->prec, f->sign):
		ft_ftoe(n, f->prec, f->sign);
	if (!!(f->sign & 1))
		ft_chcase(&tmp, &ft_toupper);
	pfs_write(out, pf_fill(f, &tmp), -1);
	free(tmp);
	return (1);
}
