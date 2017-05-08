/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mba <mba@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/12 10:28:52 by zsmith            #+#    #+#             */
/*   Updated: 2016/12/19 15:57:34 by mba              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# include <wchar.h>
# include "libft.h"

typedef struct		s_a_list
{
	int				minus;
	int				plus;
	int				hash;
	int				space;
	int				zero;
	char			*len_f;
	int				width;
	int				w_star;
	int				prec;
	char			*color;
	int				p_star;
	char			con_typ;
	int				extra;
	void			(*f)(struct s_a_list *obj, va_list args);
	char			*str;
	struct s_a_list	*next;
}					t_conv_obj;

typedef struct		s_z_list
{
	char			f_nm;
	void			(*f)(struct s_a_list *obj, va_list args);
}					t_f_list;

extern t_f_list g_func_arr[16];
extern char	*g_flag_norm;
extern char *g_flag_length;

/*
**		ft_printf
*/
int					pop_obj(t_conv_obj *obj, char **sentinel);
int					mission_control(char **sentinel, va_list args);
int					ft_printf(char *sentinel, ...);

/*
**		funx__help
*/
char				*ft_itoa3(long long nbr);

/*
**		funx__flag
*/
void				plus_func(t_conv_obj *obj);
void				space_flag(t_conv_obj *obj);
int					ft_strc(char *str, char c);
void				star_args(t_conv_obj *obj, va_list args);
int					utf_len(wchar_t *wide);

/*
**		funx__list
*/
void				ft_lstadd_end(t_conv_obj *temp, t_conv_obj *new);
int					ft_putobj(t_conv_obj *t);
t_conv_obj			*new_conv_obj(void);

/*
**		funx__pop
*/
void				pop_str(t_conv_obj *obj, char **str);
void				pop_flags(t_conv_obj *obj, char **sentinel);
void				pop_width(t_conv_obj *obj, char **sentinel);
void				pop_precision(t_conv_obj *obj, char **sentinel);

/*
** 		funx__pop2
*/
void				pop_length(t_conv_obj *obj, char **sentinel);
void				pop_con(t_conv_obj *obj, char **sentinel);
void				pop_parse(t_conv_obj *obj, char **sentinel);
int					star_check(t_conv_obj *obj, char **sentinel);
void				pop_color(t_conv_obj *obj, char **sentinel);

/*
**		funx__wide
*/
char				*s_wide(wchar_t wide);

/*
**		funx_b
*/
void				b_func(t_conv_obj *obj, va_list args);

/*
**		funx_d
*/
void				big_d_func(t_conv_obj *obj, va_list args);
void				d_func(t_conv_obj *obj, va_list args);
void				d_width(t_conv_obj *obj);
void				d_precision(t_conv_obj *obj);
void				d_width_zero(t_conv_obj *obj);

/*
**		funx_o
*/
void				o_func(t_conv_obj *obj, va_list args);
void				big_o_func(t_conv_obj *obj, va_list args);
void				casting(t_conv_obj *obj, va_list args, int n);

/*
**		funx_pi
*/
void				p_func(t_conv_obj *obj, va_list args);
void				i_func(t_conv_obj *obj, va_list args);
void				non_func(t_conv_obj *obj, va_list args);

/*
**		funx_s
*/
void				s_func(t_conv_obj *obj, va_list args);
void				big_s_func(t_conv_obj *obj, va_list args);
void				big_c_func(t_conv_obj *obj, va_list args);

/*
**		funx_u
*/
void				u_func(t_conv_obj *obj, va_list args);
void				big_u_func(t_conv_obj *obj, va_list args);
void				c_func(t_conv_obj *obj, va_list args);

/*
**		funx_x
*/
void				x_func(t_conv_obj *obj, va_list args);
void				big_x_func(t_conv_obj *obj, va_list args);
void				x_hash(t_conv_obj *obj);
void				x_hash_alt(t_conv_obj *obj);

#endif
