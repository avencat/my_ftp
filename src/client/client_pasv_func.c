/*
** client_pasv_func.c for my_ftp in /home/vencat_a/rendu/PSU/PSU_2015_myftp/src/client
** 
** Made by Axel Vencatareddy
** Login   <vencat_a@epitech.net>
** 
** Started on  Sat May 14 14:10:38 2016 Axel Vencatareddy
** Last update Sat May 14 14:10:39 2016 Axel Vencatareddy
*/

#include "client.h"

void		my_sec_ip(char (*ip)[17], int i[2])
{
  char		*tmp;

  tmp = strtok(NULL, ",");
  i[1] = 0;
  while (tmp && tmp[i[1]])
    (*ip)[i[0]++] = tmp[i[1]++];
  (*ip)[i[0]++] = '.';
  tmp = strtok(NULL, ",");
  i[1] = 0;
  while (tmp && tmp[i[1]])
    (*ip)[i[0]++] = tmp[i[1]++];
}

char		*my_ip(char *cmd)
{
  char		ip[17];
  char		*tmp;
  int		i[2];

  if (!cmd)
    return (NULL);
  tmp = strtok(cmd, ",");
  i[0] = 0;
  i[1] = 0;
  memset(ip, 0, 17);
  while (tmp && tmp[i[1]])
    ip[i[0]++] = tmp[i[1]++];
  tmp = strtok(NULL, ",");
  ip[i[0]++] = '.';
  i[1] = 0;
  while (tmp && tmp[i[1]])
    ip[i[0]++] = tmp[i[1]++];
  ip[i[0]++] = '.';
  my_sec_ip(&ip, i);
  return (strdup(ip));
}
