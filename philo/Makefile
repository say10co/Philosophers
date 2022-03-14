# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Maakefile                                          :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adriouic <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/04 15:30:58 by adriouic          #+#    #+#              #
#    Updated: 2022/03/06 22:16:23 by adriouic         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = main.c emulation.c utils.c atoi.c init.c 

NAME = philo

FLAGS = -Wall -Werror -Wextra

all: $(NAME)

$(NAME): $(SRC)
	cc $(FLAGS) $(SRC) -o $(NAME)

clean:
	
fclean:	clean
	rm -rf $(NAME)

re : fclean all

