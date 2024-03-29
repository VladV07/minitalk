/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stapioca <stapioca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 12:10:46 by cblanca           #+#    #+#             */
/*   Updated: 2022/03/22 22:09:20 by stapioca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <unistd.h>
# include <signal.h>
# include <sys/types.h>

typedef struct s_stract
{
	int		bit_count;
	int		sg1;
	int		flag_do;
}	t_data;

/* UTILS */

void		ft_putnbr_fd(int n, int fd); //
size_t		ft_strlen(char *s); //
void		*ft_memset(void *dest, int c, size_t len);
int			ft_atoi(const char *s);

/* CLIENT */

int			push_char(pid_t pid, char c);
void		server_answered(int signal_num, siginfo_t *info, void *old_info);

/* SERVER */

void		print_pid(void);
void		compose_bite(int signal_num, siginfo_t *info, void *old_info);
void		print_bite(int *bits, char *c, siginfo_t *info);

#endif