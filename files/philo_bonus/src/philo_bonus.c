/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffierro- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 00:26:20 by ffierro-          #+#    #+#             */
/*   Updated: 2025/04/27 18:57:03 by ffierro-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

int	ft_error_usage(void)
{
	printf(
		"Usage: ./philo\t[INT] <number_of_philosophers>\n"
		"\t\t[INT] <time_to_die>\n"
		"\t\t[INT] <time_to_eat>\n"
		"\t\t[INT] <time_to_sleep>\n"
		"\t\t[INT] (OPTIONAL) <times_each_philosopher_must_eat>\n"
		);
	return (1);
}

int	main(int argc, char **argv)
{
	t_core	core;

	if (!check_args(argc, argv))
		return (ft_error_usage());
	if (!init_core(&core, argc, argv))
		return (1);
	start_meal(&core);
	clear_memory(&core, core.num_philo, 1);
	return (0);
}
