/*
** ftp_sockets.c for PSU_2015_myftp
**
** Made by	Axel Vencatareddy
** Login	vencat_a
**
** Started on	Fri May 13 20:31:48 2016 Axel Vencatareddy
** Last update	Fri May 13 20:32:03 2016 Axel Vencatareddy
*/

#include "functions_ptr.h"

void		close_my_sockets(t_ptr *struc)
{
  if (struc->mode != NOPE)
    close_socket(struc->data_fd);
  if (struc->mode == PASV)
    close_socket(struc->data_socket);
}
