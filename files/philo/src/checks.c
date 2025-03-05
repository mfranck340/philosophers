/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffierro- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 00:25:46 by ffierro-          #+#    #+#             */
/*   Updated: 2025/03/05 00:25:53 by ffierro-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	if (i == n)
		return (0);
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

int	is_correct_arg(char *argv, int i)
{
	int	j;
	int	len;

	j = 0;
	while (argv[j])
	{
		if (!ft_isdigit(argv[j]))
		{
			printf("Error: Argument '%d' is not a positive number\n", i);
			return (0);
		}
		j++;
	}
	len = ft_strlen(argv);
	if (len > 10 || (len == 10 && ft_strncmp(argv, "2147483647", 10) > 0))
	{
		printf("Error: Argument '%d' is too long\n", i);
		return (0);
	}
	if (len == 1 && argv[0] == '0')
	{
		printf("Error: Argument '%d' is 0\n", i);
		return (0);
	}
	return (1);
}

int	check_args(int argc, char **argv)
{
	int	i;

	if (argc != 5 && argc != 6)
	{
		printf("Error: Wrong number of arguments\n");
		return (0);
	}
	i = 1;
	while (i < argc)
	{
		if (!is_correct_arg(argv[i], i))
			return (0);
		i++;
	}
	return (1);
}
