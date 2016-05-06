/*
** server.h for PSU_2015_myftp
**
** Made by	Axel Vencatareddy
** Login	vencat_a
**
** Started on	Sun Apr 24 14:21:01 2016 Axel Vencatareddy
** Last update	Fri May 06 17:30:00 2016 Axel Vencatareddy
*/

#ifndef SERVER_H_
# define SERVER_H_

# define BUFSIZE	1024

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <pthread.h>
# include "socket_prot.h"
# include "my_string_prot.h"

typedef enum { false, true } bool;

typedef struct	s_ptr
{
  char		**tab;
  int		client_fd;
  int		server_fd;
  char		*user;
  bool		is_connected;
  bool		end;
}		t_ptr;

int		functions_ptr(t_ptr *);

#endif /* !SERVER_H_ */
