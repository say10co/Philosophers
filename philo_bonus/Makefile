# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adriouic <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/11 19:13:17 by adriouic          #+#    #+#              #
#    Updated: 2022/03/15 18:48:15 by adriouic         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_bonus

SRC = ft_atoi.c init.c main.c utils.c additional_check.c

CFLAGS = -Wall -Werror -Wextra 

OBJS = ${SRC:.c=.o}

all: $(NAME)

%.o:%.c
	cc -c $< -o ${<:.c=.o}

$(NAME): $(OBJS)
	cc $(CFLAGS) $(OBJS) $(S) -o $@ 

clean:
	rm -rf $(OBJS)

fclean:clean
	rm -rf $(NAME)

re: fclean all
