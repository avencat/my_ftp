/*
** ftp_sockets.c for my_ftp in /home/vencat_a/rendu/PSU/PSU_2015_myftp/src/server
** 
** Made by Axel Vencatareddy
** Login   <vencat_a@epitech.net>
** 
** Started on  Sat May 14 14:14:18 2016 Axel Vencatareddy
** Last update Sat May 14 14:14:19 2016 Axel Vencatareddy
*/

#include "functions_ptr.h"

void		close_my_sockets(t_ptr *struc)
{
  if (struc->mode != NOPE)
    close_socket(struc->data_fd);
  if (struc->mode == PASV)
    close_socket(struc->data_socket);
}
