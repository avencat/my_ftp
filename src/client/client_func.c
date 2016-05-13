/*
** client_func.c for PSU_2015_myftp
**
** Made by	Axel Vencatareddy
** Login	vencat_a
**
** Started on	Wed May 11 18:57:03 2016 Axel Vencatareddy
** Last update	Sat May 14 00:31:07 2016 Axel Vencatareddy
*/

#include "client.h"

int		my_exit(t_client *cl)
{
  send_msg(cl->fd_server, cl->line);
  cl->is_end = true;
  return (0);
}

int		close_my_sockets(t_client *cl)
{
  if (cl->mode != NOPE)
    close_socket(cl->fd_data);
  cl->fd_socket = -1;
  return (0);
}

int		my_cl_list(t_client *cl)
{
  char		*cmd;

  send_msg(cl->fd_server, cl->line);
  if (cl->mode == NOPE)
    return (0);
  cmd = recv_cmd(cl->fd_server);
  fputs(cmd, stdout);
  free(cmd);
  cmd = recv_cmd(cl->fd_data);
  fputs(cmd, stdout);
  free(cmd);
  close_socket(cl->fd_data);
  cl->fd_data = -1;
  cl->mode = NOPE;
  return (0);
}
