/*
** socket_prot.h for PSU_2015_myftp
**
** Made by	Axel Vencatareddy
** Login	vencat_a
**
** Started on	Sun Apr 24 14:30:15 2016 Axel Vencatareddy
** Last update	Fri May 06 14:43:16 2016 Axel Vencatareddy
*/

#ifndef SOCKET_PROT_H_
# define SOCKET_PROT_H_

# include <netdb.h>

# define NB_CLIENTS_MAX	42

int	open_socket();
int	close_socket(int fd_sock);
int	init_socket(int fd_sock, int port);
int	listen_socket(int fd_sock);
int	connect_socket(int fd_sock, int port, char *ip);
int	send_msg(int fd, char *msg);
char	*recv_cmd(int fd_sock);
int	accept_socket(int sock_fd);

#endif /* !SOCKET_PROT_H_ */
