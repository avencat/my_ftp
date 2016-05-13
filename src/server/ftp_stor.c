/*
** ftp_other_func.c for PSU_2015_myftp
**
** Made by	Axel Vencatareddy
** Login	vencat_a
**
** Started on	Mon May 09 10:13:12 2016 Axel Vencatareddy
** Last update	Fri May 13 11:48:01 2016 Axel Vencatareddy
*/

#include "functions_ptr.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int	my_stor_end(t_ptr *struc, int file)
{
  char	buf[BUFSIZE];
  int	count;

  while ((count = read(struc->data_fd, buf, BUFSIZE)) > 0)
    {
      write(file, buf, count);
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

int	my_stor(t_ptr *struc)
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
      if ((file = open(struc->tab[1], O_RDWR | O_CREAT)) == -1)
        return (send_msg(struc->client_fd, "450 Permission denied.\r\n"));
      send_msg(struc->client_fd, "150 Opening ASCII mode data connection.\r\n");
      if (my_stor_end(struc, file) == -1)
        return (-1);
      close_socket(struc->data_fd);
      struc->mode = NOPE;
      send_msg(struc->client_fd, "226 Transfer complete.\r\n");
    }
  return (0);
}
