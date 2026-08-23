/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_race_conditions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shadya <shadya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/23 18:33:03 by shadya            #+#    #+#             */
/*   Updated: 2026/08/23 18:50:23 by shadya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stddef.h>
#include <pthread.h>
#include <unistd.h>

int	mails = 0;

void	*routine(void *)
{
	int	i;

	i = 0;
	while (i < 100000)
	{
		mails++;
		i++;
	}
}

/*
	Race conditions can happen when working with multiple threads.
	A race condition happens when two or more threads access shared data at the same time,
	and the final result depends on the unpredictable order in which their instructions actually get executed.
	In this example here, we can see that it causes issue when working with a large amount of incrementations,
	because incrementing a variable is actually 3 different actions behind the scene.
	To avoid race condtions, we need to use mutex (next lesson).
*/
int	main(int argc, char **argv)
{
	pthread_t	t1;
	pthread_t	t2;

	if (pthread_create(&t1, NULL, &routine, NULL) != 0)
		return (1);
	if (pthread_create(&t2, NULL, &routine, NULL) != 0)
		return (1);
	if (pthread_join(t1, NULL) != 0)
		return (1);
	if (pthread_join(t2, NULL) != 0)
		return (1);
	printf("Number of mails: %d\n", mails);
	return (0);
}
