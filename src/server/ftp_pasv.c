/*
** ftp_pasv.c for my_ftp in /home/vencat_a/rendu/PSU/PSU_2015_myftp/src/server
** 
** Made by Axel Vencatareddy
** Login   <vencat_a@epitech.net>
** 
** Started on  Sat May 14 14:13:40 2016 Axel Vencatareddy
** Last update Sat May 14 14:13:41 2016 Axel Vencatareddy
*/

#include "functions_ptr.h"
#include "socket.h"

int		actual_port(t_ptr *struc)
{
  t_sock_in	sin;
  socklen_t	len;

  len = sizeof(sin);
  if (getsockname(struc->server_fd, (struct sockaddr *)&sin, &len) == -1)
    {
      perror("getsockname");
      return (-1);
    }
  else
    return (ntohs(sin.sin_port));
}

char		**my_ip(char *tmp)
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

int		send_pasv_info(t_ptr *struc, t_sock_in sin)
{
  socklen_t	len;
  int		ip;
  char		str[BUFSIZE];
  char		**str_ip;

  len = sizeof(sin);
  if (listen_socket(struc->data_socket, 1) == -1)
    return (-1);
  if ((ip = getsockname(struc->data_socket, (struct sockaddr *)&sin, &len)) == -1)
    perror("getsockname");
  else
    {
      if ((str_ip = my_ip(inet_ntoa(sin.sin_addr))) == NULL)
        return (-1);
      sprintf(str, "227 Entering Passive Mode (%s,%s,%s,%s,%d,%d).\r\n",
              str_ip[0], str_ip[1], str_ip[2], str_ip[3], struc->data_port/256,
              struc->data_port % 256);
      send_msg(struc->client_fd, str);
      if (str_ip)
        free(str_ip);
    }
  struc->mode = PASV;
  struc->data_fd = accept_socket(struc->data_socket);
  return (0);
}

in_addr_t	my_client_ip(t_ptr *struc)
{
  t_sock_in	s_in;
  socklen_t	len;

  len = sizeof(s_in);
  if (getsockname(struc->client_fd, (struct sockaddr *)&s_in, &len) == -1)
    {
      perror("getsockname");
      return (-1);
    }
  else
    return (inet_addr(inet_ntoa(s_in.sin_addr)));
}

int		my_pasv(t_ptr *struc)
{
  t_sock_in	s_in;

  if (struc->is_connected == false)
    send_msg(struc->client_fd, "530 Please login with USER and PASS.\r\n");
  else
    {
      close_my_sockets(struc);
      struc->data_socket = open_socket();
      s_in.sin_family = AF_INET;
      s_in.sin_addr.s_addr = my_client_ip(struc);
      struc->data_port = actual_port(struc) + 1;
      s_in.sin_port = htons(struc->data_port);
      while (bind(struc->data_socket, (const struct sockaddr *)&s_in,
             sizeof(s_in)) == -1 && struc->data_port < 65536)
        {
          struc->data_port++;
          s_in.sin_port = htons(struc->data_port);
        }
      if (struc->data_port >= 65536)
        return (-1);
      if (send_pasv_info(struc, s_in) == -1)
        return (-1);
    }
  return (0);
}
