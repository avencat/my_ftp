/*
** client.c for my_ftp in /home/vencat_a/rendu/PSU/PSU_2015_myftp/src/client
** 
** Made by Axel Vencatareddy
** Login   <vencat_a@epitech.net>
** 
** Started on  Sat May 14 14:09:37 2016 Axel Vencatareddy
** Last update Sat May 14 14:09:38 2016 Axel Vencatareddy
*/

#include "client.h"

void		act_on_recv(char *line, t_client *cl, int mode)
{
  if (mode != 2)
    {
      if (cl->line)
        free(cl->line);
      cl->line = NULL;
      line = recv_cmd(cl->fd_server);
      if (line)
        fputs(line, stdout);
      if (line && strncmp("230", line, 3) == 0)
        cl->is_connected = true;
      else if (!line)
        {
          cl->is_end = true;
          printf("Sorry, connection lost with the server.\n");
        }
    }
  if (line)
    free(line);
}

void		welcome_message(int fd_sock)
{
  char		*line;

  line = recv_cmd(fd_sock);
  fputs(line, stdout);
  if (line)
    free(line);
  line = NULL;
}

int		read_line(int fd_sock, int actual_port)
{
  size_t	len;
  ssize_t	readed;
  char		*line;
  t_client	cl;
  int		ret;

  init_struct(&cl, fd_sock, actual_port);
  welcome_message(fd_sock);
  line = NULL;
  while (cl.is_end == false &&
         (readed = getline(&line, &len, stdin)) != -1)
    {
      cl.line = line;
      if (line && line[0] != '\n')
        ret = my_ptr_func(&cl);
      else
        ret = 2;
      if (ret != -1)
        act_on_recv(line, &cl, ret);
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
  if (read_line(fd_sock, atoi(av[2])) == -1)
    return (-1);
  if (close_socket(fd_sock) == -1)
    return (-1);
  return (0);
}
