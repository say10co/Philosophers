/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adriouic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 00:33:26 by adriouic          #+#    #+#             */
/*   Updated: 2022/03/15 14:08:24 by adriouic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "includes.h"

long long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + tv.tv_usec / 1000);
}

int	__init_mutex__(t_table *table)
{
	int	i;
	int	nb_philosophers;
	int	r1;
	int	r2;

	i = -1;
	nb_philosophers = table->nb_philosophers;
	while (++i < nb_philosophers)
	{
		if (pthread_mutex_init(&(table->all[i].fork), NULL))
		{
			destroy_mutexes(table, i);
			return (1);
		}
		table->all[i].id = i + 1;
		table->all[i].nb_eats_sofar = 0;
		table->all[i].table = table;
		table->all[i].survived = 0;
	}
	r1 = pthread_mutex_init(&(table->print_perission), NULL);
	r2 = pthread_mutex_init(&(table->no_iterrupt), NULL);
	if (r1 || r2)
		destroy_mutexes(table, i);
	return (r1 && r2);
}

int	check_(int *temp)
{
	if (temp[0] > 200)
	{
		free(temp);
		return (printf("Too much Philosophers to Create!\n"));
	}
	if (temp[1] < 0 || temp[2] < 0 || temp[3] < 0
		|| (temp[4] != UNDEFINED && temp[4] < 0))
	{
		free(temp);
		return (printf("Cant work with negative values\n"));
	}
	return (0);
}

int	__init_table__(t_table *table, char **argv, int ac)
{
	int	*temp;

	temp = (int *)(malloc(sizeof(int) * 5));
	if (!temp)
		return (1);
	temp[0] = ft_atoi(argv[1]);
	temp[1] = ft_atoi(argv[2]);
	temp[2] = ft_atoi(argv[3]);
	temp[3] = ft_atoi(argv[4]);
	temp[4] = UNDEFINED;
	if (ac == 6)
		temp[4] = ft_atoi(argv[5]);
	if (check_(temp))
		return (1);
	table->nb_philosophers = temp[0];
	table->time_to_die = temp[1];
	table->time_to_eat = temp[2];
	table->time_to_sleep = temp[3];
	table->nb_times_to_eat = temp[4];
	table->semulation_on = 1;
	table->no_one_left = 0;
	table->died = 0;
	free(temp);
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
