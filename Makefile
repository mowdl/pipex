# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mel-meka <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/25 18:52:03 by mel-meka          #+#    #+#              #
#    Updated: 2024/03/20 01:18:40 by mel-meka         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
AR = ar rc
RM = rm -f

LIBFT_SRCS = libft/ft_isalpha.c		libft/ft_toupper.c		\
			 libft/ft_isdigit.c		libft/ft_tolower.c		\
			 libft/ft_isalnum.c		libft/ft_strchr.c		\
			 libft/ft_isascii.c		libft/ft_strrchr.c		\
			 libft/ft_isprint.c		libft/ft_strncmp.c		\
			 libft/ft_strlen.c		libft/ft_memchr.c		\
			 libft/ft_memset.c		libft/ft_memcmp.c		\
			 libft/ft_bzero.c		libft/ft_strnstr.c		\
			 libft/ft_memcpy.c		libft/ft_atoi.c			\
			 libft/ft_memmove.c								\
			 libft/ft_strlcpy.c		libft/ft_calloc.c		\
			 libft/ft_strlcat.c		libft/ft_strdup.c		\
			 \
			 libft/ft_substr.c			\
			 libft/ft_strjoin.c			\
			 libft/ft_strtrim.c			\
			 libft/ft_split.c			\
			 libft/ft_itoa.c			\
			 libft/ft_strmapi.c			\
			 libft/ft_striteri.c		\
			 libft/ft_putchar_fd.c		\
			 libft/ft_putstr_fd.c		\
			 libft/ft_putendl_fd.c		\
			 libft/ft_putnbr_fd.c		\
			   libft/ft_lstnew_bonus.c			\
			   libft/ft_lstadd_front_bonus.c	\
			   libft/ft_lstsize_bonus.c			\
			   libft/ft_lstlast_bonus.c			\
			   libft/ft_lstadd_back_bonus.c		\
			   libft/ft_lstdelone_bonus.c		\
			   libft/ft_lstclear_bonus.c		\
			   libft/ft_lstiter_bonus.c			\
			   libft/ft_lstmap_bonus.c			\

GNL_SRCS = ./get_next_line/get_next_line.c \

MM_VECTOR_SRCS = ./mm_vector/vector.c		\
				 ./mm_vector/vector_ops.c

FT_PRINTF_SRCS = ./ft_printf/ft_printf.c	\
				 ./ft_printf/ft_put_hex.c	\
				 ./ft_printf/ft_put_str.c	\
				 ./ft_printf/put_int.c		\
				 ./ft_printf/ft_putchar.c	\

PIPEX_SRCS = pipex.c			\
			 execute_cmd.c		\
			 pipex_error.c

FT_PRINTF_OBJS = $(FT_PRINTF_SRCS:.c=.o)
GNL_OBJS = $(GNL_SRCS:.c=.o)
LIBFT_OBJS = $(LIBFT_SRCS:.c=.o)
MM_VECTOR_OBJS = $(MM_VECTOR_SRCS:.c=.o)
PIPEX_OBJS = $(PIPEX_SRCS:.c=.o)
SRCS = $(GNL_SRCS) $(LIBFT_SRCS) $(FT_PRINTF_SRCS) $(MM_VECTOR_OBJS)
OBJS = $(SRCS:.c=.o)
PIPEX_OBJS = $(PIPEX_SRCS:.c=.o)

INCLUDES = -I ./libft -I ./get_next_line -I ./ft_printf -I ./mm_vector


NAME = pipex


CFLAGS = -Wall -Wextra -Werror -g $(INCLUDES)

all: $(NAME)

$(NAME): $(OBJS) $(MLX) $(PIPEX_OBJS)
	$(CC) $^ -o $@


$(PIPEX_OBJS): $(PIPEX_SRCS)
	$(CC) $(CFLAGS) $(PIPEX_SRCS) -c



clean:
	$(RM) $(OBJS) $(PIPEX_OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all
