/*
** struct.c for PSU_2015_myftp
**
** Made by	Axel Vencatareddy
** Login	vencat_a
**
** Started on	Wed May 11 20:03:14 2016 Axel Vencatareddy
** Last update	Thu May 12 16:13:31 2016 Axel Vencatareddy
*/

#include "client.h"

void		init_struct(t_client *cl, int fd_sock)
{
  cl->is_end = false;
  cl->tab = NULL;
  cl->fd_server = fd_sock;
  cl->mode = NOPE;
  cl->is_connected = false;
  cl->fd_data = -1;
  cl->fd_socket = -1;
}
