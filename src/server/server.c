/*
** main.c for PSU_2015_myftp
**
** Made by	Axel Vencatareddy
** Login	vencat_a
**
** Started on	Sat Apr 23 19:08:36 2016 Axel Vencatareddy
** Last update	Thu May 12 15:44:10 2016 Axel Vencatareddy
*/

#include "server.h"

int		receive(int fd_sock, int fd_client, char *root_dir)
{
  char		*cmd;
  t_ptr		my_struc;

  init_struc(&my_struc, fd_client, fd_sock, root_dir);
  send_msg(fd_client, "220 (vsFTPd 3.0.0)\r\n");
  while (my_struc.end == false && (cmd = recv_cmd(fd_client)))
    {
      my_struc.tab = my_str_to_wordtab(cmd);
      functions_ptr(&my_struc);
      free(cmd);
      cmd = NULL;
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

int		server(int fd_sock, int fd_client, char *root_dir)
{
  if (receive(fd_sock, fd_client, root_dir) == -1)
    return (-1);
  if (close(fd_client) == -1)
    return (-1);
  return (0);
}

int		accept_all_clients(int fd_sock, char *root_dir)
{
  int		client_fd;
  pid_t		pid_fork;
  int		nb_childs;

  nb_childs = 0;
  while (nb_childs < NB_CLIENTS_MAX)
    {
      if ((client_fd = accept_socket(fd_sock)) == -1)
        {
          close_socket(fd_sock);
          return (-1);
        }
      if ((pid_fork = fork()) == -1)
        {
          close_socket(fd_sock);
          return (-1);
        }
      else if (pid_fork == 0)
        {
          if (server(fd_sock, client_fd, root_dir) == -1)
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
      printf("Usage: ./server [port] [path]\n");
      return (-1);
    }
  if (chdir(av[2]) == -1)
    {
      fprintf(stderr, "Invalid path: %s\n", av[2]);
      return (-1);
    }
  if ((fd_sock = open_socket()) == -1)
    return (-1);
  if (init_socket(fd_sock, atoi(av[1])) == -1)
    return (-1);
  printf("Hello !\nServer port: %s\nPATH of the Anonymous account: %s\
\nUse ^C to QUIT.\n", av[1], av[2]);
  if (listen_socket(fd_sock, NB_CLIENTS_MAX) == -1)
    return (-1);
  if (accept_all_clients(fd_sock, strdup(av[2])) == -1)
    return (-1);
  if (close_socket(fd_sock) == -1)
    return (-1);
  return (0);
}
