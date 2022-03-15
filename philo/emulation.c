/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   emulation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adriouic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 21:46:38 by adriouic          #+#    #+#             */
/*   Updated: 2022/03/15 14:22:13 by adriouic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

int	get_ready_to_eat(t_philo *philo, t_philo *rigth_philo)
{
	t_table			*table;

	table = philo->table;
	pthread_mutex_lock(&(philo->fork));
	print_staus(table, philo->id, "has taken a fork");
	rigth_philo = &(table->all[philo->id % table->nb_philosophers]);
	if (table->nb_philosophers == 1)
	{
		pthread_mutex_unlock(&(philo->fork));
		while (table->semulation_on)
			;
	}
	pthread_mutex_lock(&(rigth_philo->fork));
	print_staus(table, philo->id, "has taken a fork");
	pthread_mutex_lock(&(table->no_iterrupt));
	print_staus(table, philo->id, "is eating");
	philo->last_meal = get_time();
	philo->survived = 1;
	pthread_mutex_unlock(&(table->no_iterrupt));
	ft_usleep(table->time_to_eat * 1000);
	philo->survived = 0;
	philo->nb_eats_sofar += 1;
	pthread_mutex_unlock(&(rigth_philo->fork));
	pthread_mutex_unlock(&(philo->fork));
	return (0);
}

void	wait_fornext_round(t_table *table, t_philo *philo)
{
	print_staus(table, philo->id, "is sleeping");
	ft_usleep(table->time_to_sleep * 1000);
	print_staus(table, philo->id, "is thinking");
	return ;
}

void	*emulate(void *thread)
{
	t_philo	*philo;
	t_table	*table;

	philo = (t_philo *)thread;
	table = philo->table;
	if (philo->id % 2 == 0)
		usleep(1000);
	while (table->semulation_on)
	{
		if ((philo->nb_eats_sofar >= table->nb_times_to_eat
				&& table->nb_times_to_eat != UNDEFINED) || table->no_one_left)
			return (0);
		if (table->semulation_on)
		{
			if (!get_ready_to_eat(philo, NULL))
				wait_fornext_round(table, philo);
		}
	}
	return (0);
}

int	check_all_meals(t_table *table)
{
	int		i;
	int		nb_philosophers;
	t_philo	*all;

	nb_philosophers = table->nb_philosophers;
	all = table->all;
	i = -1;
	while (++i < nb_philosophers)
	{
		if (table->nb_times_to_eat == UNDEFINED
			|| all[i].nb_eats_sofar < table->nb_times_to_eat)
			return (0);
	}
	table->no_one_left = 1;
	table->semulation_on = 0;
	return (1);
}
