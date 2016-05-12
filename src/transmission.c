/*
** transmission.c for PSU_2015_myftp
**
** Made by	Axel Vencatareddy
** Login	vencat_a
**
** Started on	Tue Apr 26 17:46:13 2016 Axel Vencatareddy
** Last update	Wed May 11 22:53:47 2016 Axel Vencatareddy
*/

#include "transmission.h"

int		send_msg(int fd, char *msg)
{
  if (write(fd, msg, strlen(msg)) == -1)
    {
      perror("write() error");
      return (-1);
    }
  return (0);
}

int		accept_socket(int sock_fd)
{
  t_sock_in	s_in;
  socklen_t	size;
  int		client_fd;

  size = sizeof(s_in);
  if ((client_fd = accept(sock_fd, (struct sockaddr *)&s_in, &size)) == -1)
    {
      perror("accept() error");
      return (-1);
    }
  return (client_fd);
}

char		*recv_cmd(int fd_sock)
{
  char		buf[2048];
  int		len;

  memset(buf, 0, 2048);
  if ((len = read(fd_sock, buf, 2048)) == -1)
    {
      perror("read() error");
      return (NULL);
    }
  return (strdup(buf));
}
