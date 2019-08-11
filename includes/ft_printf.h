/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ujyzene <ujyzene@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/30 00:12:13 by ujyzene           #+#    #+#             */
/*   Updated: 2019/08/10 23:38:17 by ujyzene          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include <libft.h>

#define PF_BUFFSIZE 32

#define SCPY(s1, s2) (ft_strcpy(s1, s2) + ft_strlen(s2))
#define MSET(s1, ch, len) (ft_memset(s1, ch, len) + len)
#define SCAT(s1, s2) (ft_strcat(s1, s2) + ft_strlen(s2))
#define SIGN(ch) (ch == 43 || ch == 45)

#define M_HALF		(1 << 0)
#define M_HHALF		(1 << 1)
#define M_LONG		(1 << 2)
#define M_LLONG		(1 << 3)
#define M_SIZET		(1 << 4)
#define M_MAXT		(1 << 5)
#define M_LDOUBLE	(1 << 6)

typedef unsigned char uc;

typedef struct	s_pfs
{
	char	*s;
	int		len;
	int		last;
}				t_pfs;

/*
** opt
** 00
** bit 1 - low / up case
** bit 2 - alt (p for uint, e conv. for float)
*/

typedef struct	s_format
{
	int		prec;
	int		width;
	uc		mod;
	uc		alt;
	char	pad;
	uc		left;
	uc		sign;
	uc		base;
	uc		opt;
}				t_format;

t_pfs	pfs_init(void);
extern int		pfs_write(t_pfs *output, char *s, size_t len);

int			ft_printf(const char *format, ...);
int			pf_vprintf(char *format, va_list args);
int			pf_parse(char **format, va_list args, t_pfs *out);

extern int			pf_parce_flag(char **format, t_format *f);
extern int			pf_parce_wp(char **format, va_list args, t_format *f);
extern int			pf_parce_mod(char **format, t_format *f);

int			pf_get_spec(char **fomrat, t_format *f, va_list args,
					t_pfs *out);

char		*pf_fill(t_format *f, char **str);

int			pf_pointer_handler(t_format *f, va_list args, t_pfs *out);
int			pf_int_handler(t_format *f, va_list args, t_pfs *out);
int			pf_uint_handler(t_format *f, va_list args, t_pfs *out);
int			pf_char_handler(t_format *f, va_list args, t_pfs *out);
int			pf_string_handler(t_format *f, va_list args, t_pfs *out);
int			pf_float_handler(t_format *f, va_list args, t_pfs *out);
#endif

