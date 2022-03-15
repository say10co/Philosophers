# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Maakefile                                          :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adriouic <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/04 15:30:58 by adriouic          #+#    #+#              #
#    Updated: 2022/03/15 18:23:17 by adriouic         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = main.c emulation.c utils.c atoi.c init.c additional_check.c


OBJS = ${SRC:.c=.o}

NAME = philo

FLAGS = -Wall -Werror -Wextra

all: $(NAME)

%.o:%.c
	cc -c $(FLAGS) $< -o ${<:.c=.o}

$(NAME): $(OBJS)
	cc $(FLAGS) $(OBJS) -o $(NAME)

clean:
	rm -rf $(OBJS)

fclean:	clean
	rm -rf $(NAME)

re : fclean all

