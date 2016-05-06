/*
** main.c for PSU_2015_myftp
**
** Made by	Axel Vencatareddy
** Login	vencat_a
**
** Started on	Sat Apr 23 19:03:52 2016 Axel Vencatareddy
** Last update	Thu Apr 28 00:35:58 2016 Axel Vencatareddy
*/

#include "client.h"

int		read_line(int fd_sock)
{
  size_t	len;
  ssize_t	readed;
  char		*line;

  line = NULL;
  while ((readed = getline(&line, &len, stdin)) != -1)
    {
      printf("Réception d'une ligne de longueur %zu :\n", readed);
      printf("%s", line);
      send_msg(fd_sock, line);
      if (line)
        free(line);
      line = NULL;
      line = recv_cmd(fd_sock);
      printf("Server sent: %s\n", line);
      if (line)
        free(line);
      line = NULL;
    }
  if (line)
    free(line);
  line = NULL;
  return (0);
}

int		main(int ac, char **av)
{
  int		fd_sock;

  if (ac < 3)
    {
      printf("Usage: ./client [host] [port]\n");
      return (-1);
    }
  if ((fd_sock = open_socket()) == -1)
    return (-1);
  if (connect_socket(fd_sock, atoi(av[2]), av[1]) == -1)
    return (-1);
  printf("host: %s\nport: %s\n", av[1], av[2]);
  if (read_line(fd_sock) == -1)
    return (-1);
  if (close_socket(fd_sock) == -1)
    return (-1);
  return (0);
}
