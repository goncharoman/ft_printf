/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_vprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ujyzene <ujyzene@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/30 00:25:01 by ujyzene           #+#    #+#             */
/*   Updated: 2019/08/07 18:10:39 by ujyzene          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

int	pf_vprintf(char *format, va_list args)
{
	t_pfs	out;

	out = pfs_init();
	while (*format)
	{
		if (*format == '%')
		{
			if (!*++format)
				break ;
			if (!pf_parse(&format, args, &out))
				continue;
		}
		else
			pfs_write(&out, format, 1);
		format++;
	}
	write(1, out.s, out.last);
	free(out.s);
	return (out.last);
}
