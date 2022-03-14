/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adriouic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 19:17:34 by adriouic          #+#    #+#             */
/*   Updated: 2022/03/07 17:39:07 by adriouic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

void	destroy_mutexes(t_table *table)
{
	int	i;
	int	nb_philosophers;

	nb_philosophers = table->nb_philosophers;
	i = -1;
	while (++i < nb_philosophers)
		pthread_mutex_destroy(&(table->all[i].fork));
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
	__init_mutex__(&table);
	if (__init_threads__(&table))
		return (2);
	fallen_angel(&table);
	destroy_mutexes(&table);
	return (0);
}
