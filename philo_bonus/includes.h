/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   includes.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adriouic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 17:36:12 by adriouic          #+#    #+#             */
/*   Updated: 2022/03/15 18:42:12 by adriouic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INCLUDES_H
# define INCLUDES_H

# define UNDEFINED -42

# include <stdio.h>
# include <string.h>
# include <signal.h>
# include <sys/types.h>
# include <unistd.h>
# include <stdlib.h>
# include <semaphore.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_required
{
	sem_t		*forks;
	sem_t		*perminssion;
	sem_t		*end_of_all;
	sem_t		*is_alive;
	sem_t		*one_out;
	sem_t		*tmp;
	pid_t		*all;
	int			time_to_eat;
	int			time_to_sleep;
	int			time_to_die;
	int			nb_philosphers;
	int			ate;
	long long	start_time;
	int			id;
	long long	las_meal;
	int			died;
	int			nb_eats;
	int			nb_meals;
	int			check;
}t_required;

pid_t		*create_philo(void *(*f)(t_required), t_required *table);
int			__init_table(t_required *table, char **argv, int ac);
long long	get_time(void);
int			ft_atoi(const char *str);
int			ft_strlen(const char *s);
void		ft_usleep(unsigned int n);
void		ft_usleep(unsigned int n);
void		*watcher(void *arg);
void		print_status(long long t, int id, char *suffix, sem_t *perminssion);
int			all_alive(t_required *all);
int			all_digits(char **s);

#endif
