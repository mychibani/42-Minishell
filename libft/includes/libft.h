/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychibani <ychibani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 17:21:26 by ychibani          #+#    #+#             */
/*   Updated: 2022/05/22 17:24:49 by ychibani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# include <stddef.h>
# include <fcntl.h>
# include <stdio.h>
# define M "0123456789abcdef"
# define D "0123456789"
# define R "0123456789ABCDEF"

# ifndef BUFFER_READ
#  define BUFFER_READ 1
# endif

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}				t_list;

typedef struct t_struct
{
	char	conversion;
	int		ret;

}	t_struct;

int			ft_printf(const char *format_str, ...);
void		ft_treat_format(t_struct *content, va_list format);
void		ft_putchar(char c, t_struct *content);
void		ft_putstr(char *str, t_struct *content);
void		ft_base(unsigned long long nb, char *base, t_struct *content);
void		ft_putnbr(int n, t_struct *content);
void		ft_print_memory(void *nb, t_struct *content);
void		*ft_memset(void *b, int c, size_t len);
void		ft_striteri(char *s, void (*f)(unsigned int, char*));
void		ft_bzero(void *s, size_t n);
void		*ft_memcpy(void *dst, const void *src, size_t n);
void		*ft_memmove(void *dst, const void *src, size_t len);
void		*ft_memchr(const void *s, int c, size_t n);
size_t		ft_strlen(const char *s);
int			ft_memcmp(const void *s1, const void *s2, size_t n);
int			ft_isalpha(int c);
int			ft_isdigit(int c);
int			ft_isalnum(int c);
int			ft_isascii(int c);
int			ft_isprint(int c);
int			ft_toupper(int c);
int			ft_tolower(int c);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		*ft_strchr(const char *s, int c);
char		*ft_strrchr(const char *s, int c);
size_t		ft_strlcat(char *dst, char *src, size_t dstsize);
size_t		ft_strlcpy(char *dst, const char *src, size_t dstsize);
char		*ft_strnstr(const char *haystack, const char *needle, size_t len);
int			ft_atoi(const char *str);
void		*ft_calloc(size_t count, size_t size);
char		*ft_strdup(const char *s1);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strtrim(char const *s1, char const *set);
char		**ft_split(char const *s, char c);
char		*_strjoin(char *s1, char *s2);
char		*ft_itoa(int n);
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void		ft_putchar_fd(char c, int fd);
void		ft_putstr_fd(char *s, int fd);
void		ft_putendl_fd(char *s, int fd);
void		ft_putnbr_fd(int n, int fd);
t_list		*ft_lstnew(void *content);
void		ft_lstadd_front(t_list **alst, t_list *new);
int			ft_lstsize(t_list *lst);
t_list		*ft_lstlast(t_list *lst);
void		ft_lstadd_back(t_list **alst, t_list *new);
void		ft_lstdelone(t_list *lst, void (*del)(void *));
void		ft_lstclear(t_list **lst, void (*del)(void *));
void		ft_lstiter(t_list *lst, void (*f)(void *));
t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
char		*__gnl(int fd);

#endif
