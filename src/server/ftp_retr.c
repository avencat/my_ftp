/*
** ftp_retr.c for my_ftp in /home/vencat_a/rendu/PSU/PSU_2015_myftp/src/server
** 
** Made by Axel Vencatareddy
** Login   <vencat_a@epitech.net>
** 
** Started on  Sat May 14 14:14:05 2016 Axel Vencatareddy
** Last update Sat May 14 14:14:05 2016 Axel Vencatareddy
*/

#include "functions_ptr.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int	my_retr_end(t_ptr *struc, int file)
{
  char	buf[BUFSIZE];
  int	count;

  while ((count = read(file, buf, BUFSIZE)) > 0)
    {
      write(struc->data_fd, buf, count);
    }
  if (count == -1)
    {
      close(file);
      perror("read()");
      return (-1);
    }
  close(file);
  return (0);
}

int	my_retr(t_ptr *struc)
{
  int	file;

  if (struc->is_connected == false)
    send_msg(struc->client_fd, "530 Please login with USER and PASS.\r\n");
  else if (struc->mode == NOPE)
    send_msg(struc->client_fd, "425 Use PORT or PASV first.\r\n");
  else if (!struc->tab[1])
    send_msg(struc->client_fd, "550 Permission Denied.\r\n");
  else
    {
      if ((file = open(struc->tab[1], O_RDONLY)) == -1)
        return (send_msg(struc->client_fd, "450 Permission denied.\r\n"));
      send_msg(struc->client_fd, "150 Opening ASCII mode data connection.\r\n");
      if (my_retr_end(struc, file) == -1)
        return (-1);
      close_socket(struc->data_fd);
      struc->mode = NOPE;
      send_msg(struc->client_fd, "226 Transfer complete.\r\n");
    }
  return (0);
}
