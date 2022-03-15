/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adriouic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 19:09:54 by adriouic          #+#    #+#             */
/*   Updated: 2022/03/15 18:45:23 by adriouic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "includes.h"

int	__init_table(t_required *table, char **argv, int ac)
{
	int	tmp;
	int	i;
	int	all[5];

	i = -1;
	all[4] = UNDEFINED;
	if (ac != 5 && ac != 6)
		return (printf("Wrong nuber of arguments\n"));
	if (all_digits(argv))
		return (1);
	while (++i < ac - 1)
	{
		tmp = ft_atoi(argv[i + 1]);
		all[i] = tmp;
	}
	table->nb_philosphers = all[0];
	table->time_to_die = all[1];
	table->time_to_eat = all[2];
	table->time_to_sleep = all[3];
	table->nb_meals = all[4];
	table->ate = 0;
	table->died = 0;
	table->check = 1;
	table->nb_eats = 0;
	return (0);
}

pid_t	*create_philo(void *(*f)(t_required), t_required *table)
{
	int		i;
	int		nb_phlo;
	pid_t	pid;
	pid_t	*all;

	nb_phlo = table->nb_philosphers;
	i = -1;
	all = (pid_t *)(malloc(sizeof(pid_t) * nb_phlo));
	if (!all)
		return (0);
	all = memset(all, 0, sizeof(pid_t) * nb_phlo);
	table->start_time = get_time();
	while (++i < nb_phlo)
	{
		table->id = i + 1;
		pid = fork();
		if (pid == 0)
		{
			f(*table);
			return (0);
		}
		else
			all[i] = pid;
	}
	return (all);
}

long long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + tv.tv_usec / 1000);
}

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}
