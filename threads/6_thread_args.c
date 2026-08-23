/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   6_thread_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shadya <shadya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/23 20:19:32 by shadya            #+#    #+#             */
/*   Updated: 2026/08/23 20:44:55 by shadya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stddef.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

int	primes[10] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29 };

void	*routine(void *arg)
{
	int	i;

	i = *(int *)arg;
	printf("%d ", primes[i]);
	free(arg);
}

/*
	To pass arguments to threads, you need to malloc and pass the adresses
	of the variables. You then need to cast the variable in your routine
	if you want to use it since the arguments are always type void.
*/
int	main(int argc, char **argv)
{
	pthread_t	th[10];
	int			i;
	int			*primes_i;

	i = 0;
	while (i < 10)
	{
		primes_i = malloc(sizeof(int));
		if (!primes_i)
			return (perror("Malloc allocation failed"), 1);
		*primes_i = i;
		if (pthread_create(&th[i], NULL, &routine, primes_i) != 0)
			return (perror("Creating thread failed"), 1);
		i++;
	}
	i = 0;
	while (i < 10)
	{
		if (pthread_join(th[i], NULL) != 0)
			return (perror("Thread joint failed"), 1);
		i++;
	}
	return (0);
}
