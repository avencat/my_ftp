/*
** socket.c for PSU_2015_myftp
**
** Made by	Axel Vencatareddy
** Login	vencat_a
**
** Started on	Sun Apr 24 14:27:52 2016 Axel Vencatareddy
** Last update	Fri May 13 10:38:46 2016 Axel Vencatareddy
*/

#include "socket.h"

int		open_socket()
{
  t_protoent	*pe;
  int		fd_sock;

  if ((pe = getprotobyname("TCP")) == NULL)
    {
      perror("getprotobyname() error");
      return (-1);
    }
  if ((fd_sock = socket(AF_INET, SOCK_STREAM, pe->p_proto)) == -1)
    {
      perror("socket() error");
      return (-1);
    }
  return (fd_sock);
}

int		close_socket(int fd_sock)
{
  if (close(fd_sock) == -1)
    {
      perror("close() error");
      return (-1);
    }
  return (0);
}

int		connect_socket(int fd_sock, int port, char *ip)
{
  t_sock_in	s_in;

  s_in.sin_family = AF_INET;
  s_in.sin_port = htons(port);
  s_in.sin_addr.s_addr = inet_addr(ip);
  if (connect(fd_sock, (const struct sockaddr *)&s_in, sizeof(s_in)) == -1)
    {
      perror("connect() error");
      if (close(fd_sock) == -1)
        perror("close() error");
      return (-1);
    }
  return (0);
}

int		init_socket(int fd_sock, int port)
{
  t_sock_in	s_in;

  s_in.sin_family = AF_INET;
  s_in.sin_port = htons(port);
  s_in.sin_addr.s_addr = INADDR_ANY;
  if (bind(fd_sock, (const struct sockaddr *)&s_in, sizeof(s_in)) == -1)
    {
      perror("bind() error");
      close_socket(fd_sock);
      return (-1);
    }
  return (0);
}

int		listen_socket(int fd_sock, int nb)
{
  if (listen(fd_sock, nb) == -1)
    {
      perror("listen() error");
      close_socket(fd_sock);
      return (-1);
    }
  return (0);
}
