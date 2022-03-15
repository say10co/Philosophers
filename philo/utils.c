/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adriouic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 19:32:31 by adriouic          #+#    #+#             */
/*   Updated: 2022/03/15 14:24:20 by adriouic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"
#include <string.h>

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

void	print_staus(t_table *table, int id, char *sufix)
{
	long long	t1;

	pthread_mutex_lock(&(table->print_perission));
	if (table->semulation_on)
	{
		t1 = get_time () - table->start_time;
		printf("%lld %d %s\n", t1, id, sufix);
	}
	pthread_mutex_unlock(&(table->print_perission));
}

void	fallen_angel(t_table *table)
{
	unsigned int	p;
	unsigned int	time_to_die;
	t_philo			*all_philos;

	all_philos = table->all;
	time_to_die = table->time_to_die;
	while (table->semulation_on && !(table->no_one_left))
	{
		p = -1;
		while (++p < table->nb_philosophers)
		{
			pthread_mutex_lock(&(table->no_iterrupt));
			if (get_time() - all_philos[p].last_meal > time_to_die
				&& !all_philos[p].survived)
			{
				table->died = 1;
				print_staus(table, all_philos[p].id, "died");
				table->semulation_on = 0;
			}
			pthread_mutex_unlock(&(table->no_iterrupt));
			usleep(10);
		}
		if (table->semulation_on && check_all_meals(table))
			break ;
	}
}
