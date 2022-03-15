/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   includes.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adriouic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 19:13:39 by adriouic          #+#    #+#             */
/*   Updated: 2022/03/15 14:21:34 by adriouic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INCLUDES_H
# define INCLUDES_H
# define UNDEFINED -42

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

struct	s_table;

typedef struct s_philo
{
	long long		last_meal;
	int				id;
	int				survived;
	int				nb_eats_sofar;
	struct s_table	*table;
	pthread_mutex_t	fork;
	pthread_t		self;

}t_philo;

typedef struct s_table
{
	char			*tmp;
	int				no_one_left;
	unsigned int	time_to_eat;
	unsigned int	time_to_die;
	unsigned int	time_to_sleep;
	unsigned int	nb_philosophers;
	long long		start_time;
	int				semulation_on;
	int				nb_times_to_eat;
	int				died;
	pthread_mutex_t	no_iterrupt;
	pthread_mutex_t	print_perission;
	t_philo			*all;

}t_table;

long long		get_time(void);
int				__init_table__(t_table *table, char **argv, int ac);
int				__init_mutex__(t_table *table);
int				ft_atoi(const char *str);
void			ft_usleep(unsigned int n);
void			fallen_angel(t_table *table);
int				__init_threads__(t_table *table);
void			*emulate(void *thread);
void			print_staus(t_table *table, int id, char *sufix);
int				check_all_meals(t_table *table);
void			destroy_mutexes(t_table *table, int nb_m);

#endif
