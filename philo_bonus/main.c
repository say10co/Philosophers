/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adriouic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 22:05:44 by adriouic          #+#    #+#             */
/*   Updated: 2022/03/15 17:59:47 by adriouic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

void	takeforks_and_eat(t_required *req)
{
	int			id;
	long long	st;

	id = req->id;
	st = req->start_time;
	sem_wait(req->forks);
	print_status(get_time() - st, id, "has taken a fork", req->perminssion);
	sem_wait(req->forks);
	print_status(get_time() - st, id, "has taken a fork", req->perminssion);
	print_status(get_time() - st, id, "is eating", req->perminssion);
	sem_wait(req->tmp);
	req->las_meal = get_time();
	req->ate = 1;
	sem_post(req->tmp);
	req->nb_eats += 1;
	ft_usleep(req->time_to_eat * 1000);
	req->ate = 0;
	print_status(get_time() - st, id, "is sleeping", req->perminssion);
	sem_post(req->forks);
	sem_post(req->forks);
	ft_usleep(req->time_to_sleep * 1000);
	print_status(get_time() - st, id, "is thinking", req->perminssion);
}

void	*print_and_wait(t_required req)
{
	pthread_t	th;

	req.las_meal = req.start_time;
	if (pthread_create(&th, NULL, watcher, &req))
		return (0);
	pthread_detach(th);
	while (!req.died)
	{
		if ((req.nb_eats >= req.nb_meals && req.nb_meals != UNDEFINED))
		{
			req.ate = 1;
			sem_post(req.one_out);
			while (1)
				usleep(50 * 1000);
		}
		takeforks_and_eat(&req);
	}
	return (0);
}

static void	unlink_semaphores(void)
{
	sem_unlink("forks");
	sem_unlink("print_permission");
	sem_unlink("end_semulation");
	sem_unlink("finished");
	sem_unlink("parent_only");
	sem_unlink("temp");
}

static int	sem_created_check(t_required table, sem_t *parent_only, int c)
{
	if (c)
	{
		sem_close(table.forks);
		sem_close(table.tmp);
		sem_close(table.perminssion);
		sem_close(table.end_of_all);
		sem_close(parent_only);
		return (0);
	}
	if (table.forks == SEM_FAILED || table.perminssion == SEM_FAILED
		|| table.end_of_all == SEM_FAILED || parent_only == SEM_FAILED
		|| table.tmp == SEM_FAILED)
	{
		printf("Semaphore Creation Failed!\n");
		return (1);
	}
	return (0);
}

int	main(int ac, char **argv)
{
	t_required	table;
	pid_t		*all;	
	sem_t		*parent_only;
	int			nb_philos;

	all = NULL;
	if (__init_table(&table, argv, ac))
		return (1);
	unlink_semaphores();
	nb_philos = table.nb_philosphers;
	table.forks = sem_open("forks", O_CREAT | O_EXCL, 600, nb_philos);
	table.perminssion = sem_open("print_permission", O_CREAT | O_EXCL, 600, 1);
	table.end_of_all = sem_open("end_semulation", O_CREAT | O_EXCL, 600, 0);
	table.one_out = sem_open("finished", O_CREAT | O_EXCL, 600, 0);
	parent_only = sem_open("parent_only", O_CREAT | O_EXCL, 600, 1);
	table.tmp = sem_open("temp", O_CREAT | O_EXCL, 600, 1);
	if (sem_created_check(table, parent_only, 0))
		return (1);
	all = create_philo(print_and_wait, &table);
	table.all = all;
	sem_wait(parent_only);
	all_alive(&table);
	sem_created_check(table, parent_only, 1);
	return (0);
}
