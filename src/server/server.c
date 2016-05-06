/*
** main.c for PSU_2015_myftp
**
** Made by	Axel Vencatareddy
** Login	vencat_a
**
** Started on	Sat Apr 23 19:08:36 2016 Axel Vencatareddy
** Last update	Fri May 06 19:14:21 2016 Axel Vencatareddy
*/

#include "server.h"

int		receive(int fd_sock, int fd_client)
{
  char		*cmd;
  t_ptr		my_struc;

  my_struc.client_fd = fd_client;
  my_struc.server_fd = fd_sock;
  my_struc.end = false;
  my_struc.is_connected = false;
  my_struc.user = NULL;
  while (my_struc.end == false && (cmd = recv_cmd(fd_client)))
    {
      my_struc.tab = my_str_to_wordtab(cmd);
      functions_ptr(&my_struc);
      free(cmd);
      my_free_tab(my_struc.tab);
    }
  if (!cmd)
    {
      close(fd_client);
      return (-1);
    }
  else
    free(cmd);
  return (0);
}

int		server(int fd_sock, int fd_client)
{
  if (receive(fd_sock, fd_client) == -1)
    return (-1);
  if (close(fd_client) == -1)
    return (-1);
  return (0);
}

int		accept_all_clients(int fd_sock)
{
  int		client_fd;
  pid_t		fd_fork;
  int		nb_childs;

  nb_childs = 0;
  while (nb_childs < NB_CLIENTS_MAX)
    {
      if ((client_fd = accept_socket(fd_sock)) == -1)
        {
          close_socket(fd_sock);
          return (-1);
        }
      if ((fd_fork = fork()) == -1)
        {
          close_socket(fd_sock);
          return (-1);
        }
      else if (fd_fork == 0)
        {
          if (server(fd_sock, client_fd) == -1)
            exit(-1);
          exit(0);
        }
    }
  return (0);
}

int		main(int ac, char **av)
{
  int		fd_sock;

  if (ac < 3)
    {
      printf("Usage: ./serveur [port]\n");
      return (-1);
    }
  if ((fd_sock = open_socket()) == -1)
    return (-1);
  if (init_socket(fd_sock, atoi(av[1])) == -1)
    return (-1);
  printf("host: %s\n", av[1]);
  if (listen_socket(fd_sock) == -1)
    return (-1);
  if (accept_all_clients(fd_sock) == -1)
    return (-1);
  if (close_socket(fd_sock) == -1)
    return (-1);
  return (0);
}
