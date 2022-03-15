/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   additional_check.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adriouic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 18:19:12 by adriouic          #+#    #+#             */
/*   Updated: 2022/03/15 18:41:33 by adriouic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

int	all_digits(char **s)
{
	int	i;
	int	j;

	i = 1;
	while (s[i])
	{
		j = 0;
		while (s[i][j])
		{
			if (s[i][j] > 57 || s[i][j] < 48)
				return (printf("Argument %d has Wrong format.\
(unsigned int) required!\n", i));
			j++;
		}
		i++;
	}
	return (0);
}
