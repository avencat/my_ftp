/*
** main.c for PSU_2015_myftp
**
** Made by	Axel Vencatareddy
** Login	vencat_a
**
** Started on	Sat Apr 23 19:03:52 2016 Axel Vencatareddy
** Last update	Sun Apr 24 14:53:01 2016 Axel Vencatareddy
*/

#include "client.h"

int		main(int ac, char **av)
{
  size_t	len;
  ssize_t	readed;
  char		*line;
  int		fd_sock;

  if (ac < 3)
    return (-1);
  if ((fd_sock = open_socket()) == -1)
    return (-1);
  printf("host: %s\nport: %s\n", av[1], av[2]);
  line = NULL;
  while ((readed = getline(&line, &len, stdin)) != -1)
    {
      printf("Réception d'une ligne de longueur %zu :\n", readed);
      printf("%s", line);
    }
  if (line)
    free(line);
  if (close_socket(fd_sock) == -1)
    return (-1);
  return (0);
}
