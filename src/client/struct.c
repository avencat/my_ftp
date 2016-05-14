/*
** struct.c for my_ftp in /home/vencat_a/rendu/PSU/PSU_2015_myftp/src/client
** 
** Made by Axel Vencatareddy
** Login   <vencat_a@epitech.net>
** 
** Started on  Sat May 14 14:12:33 2016 Axel Vencatareddy
** Last update Sat May 14 14:12:34 2016 Axel Vencatareddy
*/

#include "client.h"

void		init_struct(t_client *cl, int fd_sock, int actual_port)
{
  cl->is_end = false;
  cl->tab = NULL;
  cl->fd_server = fd_sock;
  cl->mode = NOPE;
  cl->is_connected = false;
  cl->fd_data = -1;
  cl->fd_socket = -1;
  cl->actual_port = actual_port;
}
