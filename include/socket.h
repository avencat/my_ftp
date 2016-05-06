/*
** socket.h for PSU_2015_myftp
**
** Made by	Axel Vencatareddy
** Login	vencat_a
**
** Started on	Sun Apr 24 14:24:47 2016 Axel Vencatareddy
** Last update	Fri May 06 14:42:57 2016 Axel Vencatareddy
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
