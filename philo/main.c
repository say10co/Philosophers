/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adriouic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 19:17:34 by adriouic          #+#    #+#             */
/*   Updated: 2022/03/15 11:40:24 by adriouic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

void	destroy_mutexes(t_table *table, int nb_m)
{
	int	i;
	int	nb_philosophers;

	nb_philosophers = table->nb_philosophers;
	i = -1;
	while (++i < nb_m)
		pthread_mutex_destroy(&(table->all[i].fork));
	if (nb_m == nb_philosophers)
	{
		pthread_mutex_destroy(&(table->print_perission));
		pthread_mutex_destroy(&(table->no_iterrupt));
	}
}

void	join(t_philo *all, int nb_ph)
{
	int	i;

	i = -1;
	while (++i < nb_ph)
		pthread_join(all[i].self, NULL);
}

int	allocate_mem(t_table *table)
{
	t_philo	*all;

	all = (t_philo *)malloc(sizeof(t_philo) * table->nb_philosophers);
	if (!all)
		return (printf("Allocating memory failed!"));
	table->all = all;
	return (0);
}

int	main(int ac, char **argv)
{
	char	*use;
	t_table	table;

	use = "number_of_philosophers time_to_die time_to_eat time_to_sleep\
		   [number_of_times_each_philosopher_must_eat]";
	if (ac < 5 || ac > 6)
		return (printf("%s\n", use));
	if (__init_table__(&table, argv, ac))
		return (1);
	if (allocate_mem(&table))
		return (2);
	if (__init_mutex__(&table))
		return (3);
	if (__init_threads__(&table))
		return (4);
	fallen_angel(&table);
	join(table.all, table.nb_philosophers);
	destroy_mutexes(&table, table.nb_philosophers);
	free(table.all);
	return (0);
}
