/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adriouic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 00:33:26 by adriouic          #+#    #+#             */
/*   Updated: 2022/03/14 17:48:08 by adriouic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "includes.h"

int	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + tv.tv_usec / 1000);
}

void	__init_mutex__(t_table *table)
{
	int	i;
	int	nb_philosophers;

	i = -1;
	nb_philosophers = table->nb_philosophers;
	while (++i < nb_philosophers)
	{
		pthread_mutex_init(&(table->all[i].fork), NULL);
		table->all[i].id = i + 1;
		table->all[i].nb_eats_sofar = 0;
		table->all[i].table = table;
		table->all[i].survived = 0;
	}
	pthread_mutex_init(&(table->print_perission), NULL);
	pthread_mutex_init(&(table->no_iterrupt), NULL);
}

int	__init_table__(t_table *table, char **argv, int ac)
{
	int	last_arg;

	table->nb_philosophers = ft_atoi(argv[1]);
	table->time_to_die = ft_atoi(argv[2]);
	table->time_to_eat = ft_atoi(argv[3]);
	table->time_to_sleep = ft_atoi(argv[4]);
	table->semulation_on = 1;
	table->nb_times_to_eat = -42;
	table->no_one_left = 0;
	table->died = 0;
	if (ac == 6)
	{
		last_arg = ft_atoi(argv[5]);
		table->nb_times_to_eat = last_arg;
	}
	if (table->time_to_die < 0 || table->time_to_sleep < 0
		|| table->time_to_eat < 0 || last_arg < 0
		|| table->nb_philosophers > 200)
	{
		printf("Cant work with negative values\n");
		return (1);
	}
	return (0);
}

int	__init_threads__(t_table *table)
{
	int	nb_philosophers;
	int	i;

	i = -1;
	nb_philosophers = table->nb_philosophers;
	table->start_time = get_time();
	while (++i < nb_philosophers)
	{
		if (pthread_create(&(table->all[i].self), NULL,
				emulate, &(table->all[i])))
			return (1);
		table->all[i].last_meal = get_time();
	}
	return (0);
}
