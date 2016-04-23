/*
** main.c for PSU_2015_myftp
**
** Made by	Axel Vencatareddy
** Login	vencat_a
**
** Started on	Sat Apr 23 19:08:36 2016 Axel Vencatareddy
** Last update	Sat Apr 23 19:12:26 2016 Axel Vencatareddy
*/

#include "server.h"

int	main(int ac, char **av)
{
  if (ac < 2)
    return (-1);
  printf("host: %s\n", av[1]);
  return (0);
}
