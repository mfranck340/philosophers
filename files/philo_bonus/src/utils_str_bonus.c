/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_str_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffierro- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 18:45:23 by ffierro-          #+#    #+#             */
/*   Updated: 2025/04/27 18:57:45 by ffierro-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

static int	count_digits(int n)
{
	int	count;

	count = 0;
	if (n <= 0)
		count++;
	while (n != 0)
	{
		n /= 10;
		count++;
	}
	return (count);
}

static char	*ft_itoa(int n)
{
	char	*str;
	int		len;

	len = count_digits(n);
	str = (char *) malloc(sizeof(char) * (len + 1));
	if (!str)
		return (0);
	str[len] = '\0';
	if (n == -2147483648)
	{
		str[--len] = '8';
		n = n / 10;
	}
	if (n < 0)
	{
		str[0] = '-';
		n *= -1;
	}
	while (n > 9)
	{
		str[--len] = (n % 10) + '0';
		n /= 10;
	}
	str[--len] = n + '0';
	return (str);
}

static int	put_number(int id, char *name, int i)
{
	char	*id_str;
	int		j;

	id_str = ft_itoa(id);
	if (!id_str)
	{
		free(name);
		return (0);
	}
	j = 0;
	while (id_str[j])
	{
		name[i + j] = id_str[j];
		j++;
	}
	free(id_str);
	name[i + j] = '\0';
	return (1);
}

char	*get_sem_name(int id)
{
	char	*name;
	int		i;

	name = (char *)malloc(sizeof(char) * (SIZE_SEM_EAT
				+ count_digits(id) + 1));
	if (!name)
		return (0);
	i = 0;
	while (i < SIZE_SEM_EAT)
	{
		name[i] = SEM_EAT[i];
		i++;
	}
	if (!put_number(id, name, i))
		return (0);
	return (name);
}

int	ft_atoi(const char *nptr)
{
	int	i;
	int	sign;
	int	nb;

	i = 0;
	sign = 1;
	nb = 0;
	while (nptr[i] == ' ' || nptr[i] == '\t' || nptr[i] == '\n'
		|| nptr[i] == '\v' || nptr[i] == '\f' || nptr[i] == '\r')
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign = -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		nb = nb * 10 + (nptr[i] - '0');
		i++;
	}
	return (nb * sign);
}
