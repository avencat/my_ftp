/*
** ftp_port.c for my_ftp in /home/vencat_a/rendu/PSU/PSU_2015_myftp/src/server
** 
** Made by Axel Vencatareddy
** Login   <vencat_a@epitech.net>
** 
** Started on  Sat May 14 14:13:53 2016 Axel Vencatareddy
** Last update Sat May 14 14:13:53 2016 Axel Vencatareddy
*/

#include "functions_ptr.h"
#include "socket.h"

int		get_nb(char *str, int *i, int *count)
{
  int		j;
  char		port[10];

  j = 0;
  memset(port, 0, 10);
  while (str && str[*i] && (*count) < 5)
    {
      if (str[*i] >= '0' && str[*i] <= '9')
        port[j++] = str[*i];
      else if (str[*i] == ',')
        (*count)++;
      else
        return (-1);
      (*i)++;
    }
  return (atoi(port));
}

int		get_my_port(char *str)
{
  int		nb;
  int		sec;
  int		i;
  int		count;
  int		tmp_count;

  count = 0;
  i = 0;
  while (str && str[i] && count < 4)
    {
      if (str[i] == ',')
        count++;
      i++;
    }
  nb = get_nb(str, &i, &count);
  tmp_count = 4;
  sec = get_nb(str, &i, &tmp_count);
  if (count < 5 || tmp_count > 4)
    return (-1);
  return (256 * nb + sec);
}

char		*get_my_ip(char *str)
{
  char		ip[17];
  int		i;
  int		count;

  i = 0;
  count = 0;
  memset(ip, 0, 17);
  while (str && str[i] && i < 17 && count < 4)
    {
      if (str[i] == ',')
        {
          if (count < 3)
            ip[i] = '.';
          count++;
        }
      else if (str[i] >= '0' && str[i] <= '9')
        ip[i] = str[i];
      else
        return (NULL);
      i++;
    }
  ip[i] = '\0';
  return (strdup(ip));
}

int		my_port_end(t_ptr *struc, char *ip)
{
  if (connect_socket(struc->data_fd, struc->data_port, ip) == -1)
    {
      free(ip);
      send_msg(struc->client_fd, "425 Cannot Connect To The Port.\r\n");
      return (-1);
    }
  free(ip);
  struc->mode = ACTV;
  send_msg(struc->client_fd, "200 Connected To The Port.\r\n");
  return (0);
}

int		my_port(t_ptr *struc)
{
  char		*ip;

  if (!struc->tab[1])
    send_msg(struc->client_fd, "530 Please login with USER and PASS.\r\n");
  else
    {
      close_my_sockets(struc);
      if ((ip = get_my_ip(struc->tab[1])) == NULL)
        return (send_msg(struc->client_fd, "501 Bad IP Address Passed.\r\n"));
      if ((struc->data_port = get_my_port(struc->tab[1])) == -1)
        {
          free(ip);
          send_msg(struc->client_fd, "501 Bad Port Passed.\r\n");
          return (-1);
        }
      struc->data_fd = open_socket();
      return (my_port_end(struc, ip));
    }
  return (0);
}
