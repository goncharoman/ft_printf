/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ujyzene <ujyzene@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/30 01:43:04 by ujyzene           #+#    #+#             */
/*   Updated: 2019/08/11 20:16:22 by ujyzene          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

static inline t_format	format_init(void)
{
	return (t_format){
		.prec = -1,
		.width = 0,
		.mod = 0,
		.base = 0,
		.alt = 0,
		.pad = 0,
		.sign = 0,
		.opt = 0,
		.left = 0,
	};
}

static inline int		isspec(char ch)
{
	return (!!ft_strchr("%sdibBoOuUxXfFcCnp", ch));
}

static inline int		get_base(char ch)
{
	if (ch == 'X' || ch == 'x' || ch == 'p')
		return (16);
	else if (ch == 'O' || ch == 'o')
		return (8);
	else if (ch == 's' || ch == 'c' || ch == '%')
		return (0);
	return (10);
}

int						pf_parse(char **format, va_list args, t_pfs *out)
{
	t_format f;

	f = format_init();
	while (!isspec(**format))
	{
		if (!pf_parce_flag(format, &f) && (pf_parce_wp(format, args, &f) +
			pf_parce_mod(format, &f)) < 1)
			return (0);
	}
	return (pf_get_spec(format, &f, args, out));
}

int						pf_get_spec(char **conv, t_format *f, va_list args,
	t_pfs *out)
{
	static int	(*handlers[7])(t_format*, va_list, t_pfs*) = {
		NULL,
		pf_int_handler,
		pf_uint_handler,
		pf_float_handler,
		pf_char_handler,
		pf_string_handler
	};
	static int	table[] = {4, 0, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0,
		5, 0, 2, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 1, 3, 3, 3, 0, 1,
		0, 0, 0, 0, 0, 2, 2, 0, 0, 5, 0, 2, 0, 0, 2};

	f->opt |= ft_islower(**conv) + (!!ft_strchr("epU%", **conv) << 1);
	f->base = get_base(**conv);
	if (**conv == '%')
		return (pf_char_handler(f, args, out));
	if (!**conv || !handlers[table[**conv - 67]])
		return (0);
	return (handlers[table[**conv - 67]](f, args, out));
}
