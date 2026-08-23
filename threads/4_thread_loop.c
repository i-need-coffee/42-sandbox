/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_thread_loop.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shadya <shadya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/23 19:10:00 by shadya            #+#    #+#             */
/*   Updated: 2026/08/23 19:25:13 by shadya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stddef.h>
#include <pthread.h>
#include <unistd.h>

int				mails = 0;
pthread_mutex_t mutex;

void	*routine(void *)
{
	int	i;

	i = 0;
	while (i < 100000)
	{
		pthread_mutex_lock(&mutex);
		mails++;
		pthread_mutex_unlock(&mutex);
		i++;
	}
}

/*
	Copying and pasting the same piece of code multiple time is just bad programming.
	Therefore, we should use a loop to create and wait for threads.
	The logical way would be to create one loop for both functions, but you will
	encounter a big issue: the threads do no longer execute in parallel, which
	defeats the purpose. To avoid this issue, you need to create 2 loops.
*/
int	main(int argc, char **argv)
{
	pthread_t	th[4];
	int			i;

	pthread_mutex_init(&mutex, NULL);
	i = 0;
	while (i < 4)
	{
		if (pthread_create(&th[i], NULL, &routine, NULL) != 0)
		{
			perror("Create thread failed");
			return (1);
		}
		printf("Thread %d has started\n", i);
		i++;
	}
	i = 0;
	while (i < 4)
	{
		if (pthread_join(th[i], NULL) != 0)
			return (1);
		printf("Thread %d has finished execution\n", i);
		i++;
	}
	pthread_mutex_destroy(&mutex);
	printf("Number of mails: %d\n", mails);
	return (0);
}
