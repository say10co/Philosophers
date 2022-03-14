/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adriouic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 19:09:02 by adriouic          #+#    #+#             */
/*   Updated: 2022/03/14 17:33:58 by adriouic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

void	ft_usleep(unsigned int n)
{
	struct timeval	now;
	struct timeval	after;

	gettimeofday(&now, NULL);
	while (1)
	{
		gettimeofday(&after, NULL);
		if ((((after.tv_sec - now.tv_sec) * 1e6)
				+ (after.tv_usec - now.tv_usec)) > n)
			break ;
		usleep(50);
	}
}

void	print_status(int t, int id, char *suffix, sem_t *perminssion)
{
	int	r;

	sem_wait(perminssion);
	printf("%d %d %s\n", t, id, suffix);
	r = ft_strlen(suffix);
	if (r != 4)
		sem_post(perminssion);
}

void	*watcher(void *arg)
{
	t_required	*e;
	int			nb_philo;
	int			st;

	e = (t_required *)arg;
	nb_philo = e->nb_philosphers;
	st = e->start_time;
	while (1)
	{
		sem_wait(e->tmp);
		if (!e->ate && get_time() - e->las_meal > e->time_to_die)
		{
			e->died = 1;
			print_status(get_time() - st, e->id, "died", e->perminssion);
			usleep(100);
			sem_post(e->end_of_all);
			return (0);
		}
		sem_post(e->tmp);
		usleep(1000);
	}
	return (0);
}

void	*second_watcher(void *arg)
{
	t_required	*table;
	int			nb_p;
	int			i;

	i = 0;
	table = (t_required *)arg;
	nb_p = table->nb_philosphers;
	while (i < nb_p)
	{
		sem_wait(table->one_out);
		i++;
	}
	sem_post(table->end_of_all);
	return (0);
}

void	all_alive(t_required *arg)
{	
	pthread_t	second_w;
	pid_t		*all;
	int			nb_ph;
	int			i;

	i = -1;
	nb_ph = arg->nb_philosphers;
	all = arg->all;
	pthread_create(&second_w, NULL, second_watcher, arg);
	pthread_detach(second_w);
	sem_wait(arg->end_of_all);
	while (++i < nb_ph)
		kill(all[i], SIGKILL);
}
