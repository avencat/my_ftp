/*
** client_pasv.c for my_ftp in /home/vencat_a/rendu/PSU/PSU_2015_myftp/src/client
** 
** Made by Axel Vencatareddy
** Login   <vencat_a@epitech.net>
** 
** Started on  Sat May 14 14:10:12 2016 Axel Vencatareddy
** Last update Sat May 14 14:10:13 2016 Axel Vencatareddy
*/

#include "client.h"

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

  send_msg_client(cl->fd_server, cl->line);
  cmd = recv_cmd(cl->fd_server);
  fputs(cmd, stdout);
  if (cmd)
    free(cmd);
  return (2);
}

int		my_pasv_end(t_client *cl, char *ip, char *cmd, char *tmp)
{
  if ((cl->fd_data = open_socket()) == -1)
    {
      free(tmp);
      free(cmd);
      free(ip);
      return (-1);
    }
  if (connect_socket(cl->fd_data, get_my_port(), ip) == -1)
    {
      free(tmp);
      free(cmd);
      free(ip);
      close(cl->fd_data);
      return (-1);
    }
  cl->mode = PASV;
  free(cmd);
  free(ip);
  free(tmp);
  return (2);
}

int		my_pasv(t_client *cl)
{
  char		*cmd;
  char		*tmp;
  char		*ip;

  if (cl->is_connected == false)
    return (not_connected(cl));
  send_msg_client(cl->fd_server, cl->line);
  cmd = recv_cmd(cl->fd_server);
  fputs(cmd, stdout);
  if (strncmp(cmd, "227", 3) == 0)
    {
      tmp = strchr(cmd, '(') + 1;
      tmp = strdup(tmp);
      ip = my_ip(tmp);
      close_my_sockets(cl);
      return (my_pasv_end(cl, ip, cmd, tmp));
    }
  return (2);
}
