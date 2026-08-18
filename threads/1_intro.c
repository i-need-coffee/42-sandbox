/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_intro.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjolliet <sjolliet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/18 15:38:38 by sjolliet          #+#    #+#             */
/*   Updated: 2026/08/18 15:58:56 by sjolliet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stddef.h>
#include <pthread.h>
#include <unistd.h>

void	*routine(void *)
{
	printf("Test from threads\n");
	sleep(3);
	printf("Ending thread\n");
}

/*
	Introduction to threads.
	Here we can see that the threads we create exectue at the same time.
	The pthread_create() and pthread_join() functions go together,
	as the pthread_join() is used to wait for the thread to end.
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
	return (0);
}
