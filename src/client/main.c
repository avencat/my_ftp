/*
** main.c for PSU_2015_myftp
**
** Made by	Axel Vencatareddy
** Login	vencat_a
**
** Started on	Sat Apr 23 19:03:52 2016 Axel Vencatareddy
** Last update	Sat Apr 23 20:13:53 2016 Axel Vencatareddy
*/

#include "client.h"

int	main(int ac, char **av)
{
  if (ac < 3)
    return (-1);
  printf("host: %s\nport: %s\n", av[1], av[2]);
  return (0);
}
