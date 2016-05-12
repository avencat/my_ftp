/*
** client_pasv.c for PSU_2015_myftp
**
** Made by	Axel Vencatareddy
** Login	vencat_a
**
** Started on	Wed May 11 18:51:09 2016 Axel Vencatareddy
** Last update	Thu May 12 15:29:10 2016 Axel Vencatareddy
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

int		get_my_port()
{
  char		*tmp;
  int		nb;
  int		sec;

  tmp = strtok(NULL, ",");
  nb = atoi(tmp);
  tmp = strtok(NULL, ")");
  sec = atoi(tmp);
  return (nb * 256 + sec);
}

int		not_connected(t_client *cl)
{
  char		*cmd;

  send_msg(cl->fd_server, cl->line);
  cmd = recv_cmd(cl->fd_server);
  fputs(cmd, stdout);
  if (cmd)
    free(cmd);
  return (2);
}

int		my_pasv(t_client *cl)
{
  char		*cmd;
  char		*tmp;
  char		*ip;

  if (cl->is_connected == false)
    return (not_connected(cl));
  send_msg(cl->fd_server, cl->line);
  cmd = recv_cmd(cl->fd_server);
  fputs(cmd, stdout);
  if (strncmp(cmd, "227", 3) == 0)
    {
      tmp = strchr(cmd, '(') + 1;
      ip = my_ip(strdup(tmp));
      close_my_sockets(cl);
      if ((cl->fd_data = open_socket()) == -1)
        return (-1);
      if (connect_socket(cl->fd_data, get_my_port(), ip) == -1)
        {
          close(cl->fd_data);
          return (-1);
        }
      cl->mode = PASV;
      free(cmd);
    }
  return (2);
}
