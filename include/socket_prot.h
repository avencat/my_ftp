/*
** socket_prot.h for my_ftp in /home/vencat_a/rendu/PSU/PSU_2015_myftp/include
** 
** Made by Axel Vencatareddy
** Login   <vencat_a@epitech.net>
** 
** Started on  Sat May 14 14:17:10 2016 Axel Vencatareddy
** Last update Sat May 14 14:17:11 2016 Axel Vencatareddy
*/

#ifndef SOCKET_PROT_H_
# define SOCKET_PROT_H_

# include <netdb.h>

# define NB_CLIENTS_MAX	42

int	open_socket();
int	close_socket(int fd_sock);
int	init_socket(int fd_sock, int port);
int	listen_socket(int fd_sock, int nb);
int	connect_socket(int fd_sock, int port, char *ip);
int	send_msg(int fd, char *msg);
int	send_msg_client(int fd, char *msg);
char	*recv_cmd(int fd_sock);
int	accept_socket(int sock_fd);

#endif /* !SOCKET_PROT_H_ */
