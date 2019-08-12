/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_chars_handlers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ujyzene <ujyzene@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 22:48:32 by ujyzene           #+#    #+#             */
/*   Updated: 2019/08/12 11:11:08 by ujyzene          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

int	pf_char_handler(t_format *f, va_list args, t_pfs *out)
{
	char	*c;
	int		len;

	if (!(c = ft_strnew(2)))
		return (0);
	*c = !!(f->opt & 2) ? '%' : va_arg(args, int);
	if (f->prec == 0 && *c != '%')
		*c = 0;
	len = MAX(f->width, 1) - (f->left && !*c);
	if (f->left && !*c)
		pfs_write(out, "\0", 1);
	pfs_write(out, (f->width -= !*c) > (*c > 0) ? pf_fill(f, &c) : c, len);
	free(c);
	return (1);
}

int	pf_string_handler(t_format *f, va_list args, t_pfs *out)
{
	char	*tmp;

	if (!(tmp = va_arg(args, char*)))
		tmp = "(null)";
	if (!(tmp = ft_strndup(tmp, f->prec > 0 ? f->prec : ft_strlen(tmp))) ||
		(f->prec == 0 && f->width == 0))
		return (1);
	if (f->prec == 0)
		ft_memset(tmp, 0, 1);
	pfs_write(out, f->width > (int)ft_strlen(tmp) ? pf_fill(f, &tmp) :
		tmp, -1);
	free(tmp);
	return (1);
}
