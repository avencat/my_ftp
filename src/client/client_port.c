/*
** client_port.c for PSU_2015_myftp
**
** Made by	Axel Vencatareddy
** Login	vencat_a
**
** Started on	Wed May 11 18:54:50 2016 Axel Vencatareddy
** Last update	Thu May 12 15:29:06 2016 Axel Vencatareddy
*/

#include "client.h"
#include "socket.h"

int		actual_port(t_client *struc)
{
  t_sock_in	sin;
  socklen_t	len;

  len = sizeof(sin);
  if (getsockname(struc->fd_server, (struct sockaddr *)&sin, &len) == -1)
    {
      perror("getsockname");
      return (-1);
    }
  else
    return (ntohs(sin.sin_port));
}

char		**get_my_ip(char *tmp)
{
  char		**ip;

  if ((ip = malloc(sizeof(char *) * 5)) == NULL || !tmp)
    {
      perror("malloc() error");
      return (NULL);
    }
  ip[0] = strtok(tmp, ".");
  ip[1] = strtok(NULL, ".");
  ip[2] = strtok(NULL, ".");
  ip[3] = strtok(NULL, ".");
  ip[4] = NULL;
  return (ip);
}

int		send_port_info(t_client *cl, int port)
{
  char		str[BUFSIZE];
  char		**str_ip;
  char		*tmp_ip;

  if (listen_socket(cl->fd_data, 1) == -1)
    return (-1);
  tmp_ip = strdup("127.0.0.1");
  if ((str_ip = get_my_ip(tmp_ip)) == NULL)
    return (-1);
  sprintf(str, "PORT %s,%s,%s,%s,%d,%d\r\n", str_ip[0], str_ip[1], str_ip[2],
          str_ip[3], port / 256, port % 256);
  send_msg(cl->fd_server, str);
  if (str_ip)
    free(str_ip);
  if (tmp_ip)
    free(tmp_ip);
  cl->mode = ACTV;
  if (cl->fd_socket != 0)
    close_socket(cl->fd_socket);
  cl->fd_socket = cl->fd_data;
  cl->fd_data = accept_socket(cl->fd_server);
  return (0);
}

int		my_port(t_client *cl)
{
  t_sock_in	s_in;
  int		port;

  if (cl->is_connected == false)
    {
      send_msg(cl->fd_server, cl->line);
      return (0);
    }
  if (cl->mode != NOPE)
    close_socket(cl->fd_data);
  cl->fd_data = open_socket();
  s_in.sin_family = AF_INET;
  s_in.sin_addr.s_addr = inet_addr("127.0.0.1");
  port = actual_port(cl);
  s_in.sin_port = htons(port);
  while (bind(cl->fd_data, (const struct sockaddr *)&s_in,
         sizeof(s_in)) == -1 && port < 65536)
    {
      port++;
      s_in.sin_port = htons(port);
    }
  if (port >= 65536)
    return (-1);
  return (send_port_info(cl, port));
}