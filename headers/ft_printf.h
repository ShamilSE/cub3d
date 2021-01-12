/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mismene <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 12:36:56 by mismene           #+#    #+#             */
/*   Updated: 2021/01/03 16:55:51 by mismene          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct				s_structure
{
	char					*p;
	char					flag;
	int						width;
	int						accuracy;
	char					type;
	int						return_value;
	size_t					sign;
	size_t					string_size;
	va_list					args;
	int						null;
	int						met_point;
}							t_shamil;

void						proccessor(t_shamil *tab);
void						parser(t_shamil *tab);
void						router(t_shamil *tab);
void						null_flags(t_shamil *tab);
t_shamil					*create_structure(const char *string);
void						initialize_structure(t_shamil *structure);
void						null_flags(t_shamil *tab);
void						print_text(t_shamil *tab);
void						print_digits(int digit, t_shamil *tab);
void						print_unsigned(unsigned int digit, t_shamil *tab);
void						print_strings(char *string, t_shamil *tab);
void						print_chars(int c, t_shamil *tab);
void						print_pointers(unsigned long pointer,
								t_shamil *tab);
void						print_hex(unsigned int hex, t_shamil *tab);
void						print_spaces(t_shamil *tab, int digit);
void						print_minus(t_shamil *tab,
								int *digit, size_t *width);
void						print_zeroes(t_shamil *tab, size_t width);
char						*ft_itoa(int nbr);
int							ft_atoi(const char *str);
void						ft_putstr(char const *s, t_shamil *tab);
size_t						ft_strlen(const char *str);
char						*ft_strchr(const char *s, int c);
void						ft_putchar(char c, t_shamil *tab);
void						ft_putnbr(int n, t_shamil *tab);
int							ft_isdigit(int a);
int							ft_isalpha(int c);
int							ft_toupper(int c);
void						to_hex(char *str, unsigned long decimal, char type);
void						ft_bzero(void *b, size_t len);
void						print_formated_u(t_shamil *tab, unsigned int digit);
char						*ft_itoa_u(unsigned int nbr);
void						print_spaces_u(t_shamil *tab, unsigned int digit);
void						print_formated_u_p5(t_shamil *tab,
								unsigned int digit);
void						print_percent(t_shamil *tab);
char						*ft_strdup(const char *s1);
void						flag_check(t_shamil *tab);
void						width_check(t_shamil *tab);
void						pirnt_formated_volume_two(t_shamil *tab, int digit);
void						print_formated_volume_three(t_shamil *tab,
								int digit);
void						print_formated_volume_four(t_shamil *tab,
								int digit);
void						print_formated(t_shamil *tab, int digit);
void						print_formated_helper(t_shamil *tab,
								int digit, char *str);
void						print_formated_helper_p2(t_shamil *tab,
								int digit, size_t width);
void						print_formated_helper_p3(t_shamil *tab,
								int digit, size_t width);
void						print_formated_helper_p4(t_shamil *tab,
								int digit, size_t width);
void						print_formated_helper_p5(t_shamil *tab,
								int digit, size_t width);
void						print_formated_helper_p6(t_shamil *tab,
								int digit, size_t width);
void						print_formated_helper_p7(t_shamil *tab,
								int digit);
void						print_formated_helper_p8(t_shamil *tab,
								int digit, size_t width);
void						print_formated_u_p6(t_shamil *tab,
								unsigned int digit, char *str);
void						print_formated_u_p7(t_shamil *tab,
								size_t width, char *str);
void						print_formated_u_if_else(t_shamil *tab,
								int digit, char *str);
void						print_formated_u_p1(t_shamil *tab,
								unsigned int digit);
void						print_formated_u_p2(t_shamil *tab,
								unsigned int digit);
void						print_formated_u_p3(t_shamil *tab,
								unsigned int digit);
void						print_formated_u_p4(t_shamil *tab,
								unsigned int digit);
void						print_formated_hex_helper_p4(t_shamil *tab,
								char *str);
int							ft_printf(char *string, ...);
#endif
