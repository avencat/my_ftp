/*
** socket.h for my_ftp in /home/vencat_a/rendu/PSU/PSU_2015_myftp/include
** 
** Made by Axel Vencatareddy
** Login   <vencat_a@epitech.net>
** 
** Started on  Sat May 14 14:16:55 2016 Axel Vencatareddy
** Last update Sat May 14 14:16:56 2016 Axel Vencatareddy
*/

#ifndef SOCKET_H_
# define SOCKET_H_

# include <unistd.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <netdb.h>
# include <stdio.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <string.h>
# include "socket_prot.h"

typedef struct protoent		t_protoent;
typedef struct sockaddr_in	t_sock_in;

#endif /* !SOCKET_H_ */
