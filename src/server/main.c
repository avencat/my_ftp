/*
** main.c for PSU_2015_myftp
**
** Made by	Axel Vencatareddy
** Login	vencat_a
**
** Started on	Sat Apr 23 19:08:36 2016 Axel Vencatareddy
** Last update	Sun Apr 24 14:53:14 2016 Axel Vencatareddy
*/

#include "server.h"

int		main(int ac, char **av)
{
  int		fd_sock;

  if (ac < 2)
    return (-1);
  if ((fd_sock = open_socket()) == -1)
    return (-1);
  printf("host: %s\n", av[1]);
  if (close_socket(fd_sock) == -1)
    return (-1);
  return (0);
}
