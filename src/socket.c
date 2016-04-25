/*
** socket.c for PSU_2015_myftp
**
** Made by	Axel Vencatareddy
** Login	vencat_a
**
** Started on	Sun Apr 24 14:27:52 2016 Axel Vencatareddy
** Last update	Sun Apr 24 14:53:11 2016 Axel Vencatareddy
*/

#include "socket.h"

int	open_socket()
{
  t_protoent	*pe;
  int		fd;

  if ((pe = getprotobyname("TCP")) == NULL)
    return (-1);
  if ((fd = socket(AF_INET, SOCK_STREAM, pe->p_proto)) == -1)
    return (-1);
  return (fd);
}

int	close_socket(int fd)
{
  if (close(fd) == -1)
    return (-1);
  return (0);
}
