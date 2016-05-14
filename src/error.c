/*
** error.c for PSU_2015_myftp
**
** Made by	Axel Vencatareddy
** Login	vencat_a
**
** Started on	Sat May 14 12:45:53 2016 Axel Vencatareddy
** Last update	Sat May 14 12:48:01 2016 Axel Vencatareddy
*/

#include <stdio.h>

int	my_error(char *msg, int ret)
{
  perror(msg);
  return (ret);
}
