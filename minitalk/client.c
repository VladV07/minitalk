/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stapioca <stapioca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 10:37:15 by cblanca           #+#    #+#             */
/*   Updated: 2022/03/22 23:30:49 by stapioca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h> // dell
#include <stdlib.h>
#include "minitalk.h"

t_data	data;

int	main(int argc, char **argv)
{
	struct sigaction	sig2;
	int					error_flag;
	int					len;

	ft_memset(&sig2, 0, sizeof(sig2));
	sigemptyset(&sig2.sa_mask);
	sig2.sa_sigaction = server_answered;
	sig2.sa_flags = SA_SIGINFO;
	error_flag = 0;
	error_flag = sigaction(SIGUSR2, &sig2, NULL);
	error_flag = sigaction(SIGUSR1, &sig2, NULL);
	if (error_flag != 0)
		write(1, "Server: Error in sigaction\n", 27);
	if (argc == 3)
	{
		len = ft_strlen(argv[2]) + 1;
		while (len-- > 0 && error_flag == 0)
			error_flag = push_char(ft_atoi(argv[1]), *argv[2]++);
		if (error_flag != 0)
		{
			write(2, "Client: Error in transfer\n", 26);
			exit(0);
		}
		while (1)
			pause();
	}
	else
		write(2, "Wrong arguments.\n", 17);
}

int	push_char(pid_t pid, char c)
{
	//printf("c = %c\n", c); //
	int	bit_move;
	int	error_flag;

	bit_move = -1;
	error_flag = 0;
	data.bit_count = 0;
	data.sg1 = 0;
	data.flag_do = 0;
	while (++bit_move < 8 && data.bit_count < 8)
	{
		if ((c >> bit_move) & 1)
			error_flag = kill(pid, SIGUSR2);
		else
			error_flag = kill(pid, SIGUSR1);
		if (error_flag != 0 || data.sg1 != 0)
			break ;
		//printf("push_char ->pause\n"); //
		usleep(1000);
		while (1 && data.flag_do != 1)
			pause();
	}
	//printf("data.bit_count push_char= %d\n", data.bit_count); //
	//usleep(20);
	if (data.bit_count != 8)
	{
		error_flag = -1;
		write(1, "NO BIT PAK\n", 11);
	}
	// printf("push_char <-pause\n");//
	//usleep(20);
	return (error_flag);
}

void	server_answered(int signal_num, siginfo_t *info, void *old_info)
{
	//printf("server_answered\n"); //
	usleep(20);
	(void)old_info;
	(void)info;
	data.sg1 = -1;
	data.flag_do = 1;
	if (signal_num == SIGUSR1)
	{
		data.bit_count++;
		data.sg1 = 0;
		//printf("data.bit_count= %d\n", data.bit_count); //
	}
	else if (signal_num == SIGUSR2)
	{
		write(1, "Message received\n", 17);
		exit(0);
	}
}
