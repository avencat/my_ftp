/*
** main.c for PSU_2015_myftp
**
** Made by	Axel Vencatareddy
** Login	vencat_a
**
** Started on	Sat Apr 23 19:03:52 2016 Axel Vencatareddy
** Last update	Thu May 12 17:29:24 2016 Axel Vencatareddy
*/

#include "client.h"

void		init_cmp(char *cmp[7])
{
  cmp[0] = "PASV";
  cmp[1] = "PORT";
  cmp[2] = "QUIT";
  cmp[3] = "RETR";
  cmp[4] = "STOR";
  cmp[5] = "LIST";
  cmp[6] = NULL;
}

int		my_ptr_func(t_client *cl)
{
  int		(*ptr[7])(t_client *cl);
  char		*cmp[7];
  int		i;

  ptr[0] = &my_pasv;
  ptr[1] = &my_port;
  ptr[2] = &my_exit;
  ptr[3] = &my_retr;
  ptr[4] = &my_stor;
  ptr[5] = &my_cl_list;
  ptr[6] = NULL;
  init_cmp(cmp);
  i = 0;
  while (i < 6)
    {
      if (strncmp(cl->line, cmp[i], 4) == 0)
        return (ptr[i](cl));
      i++;
    }
  send_msg(cl->fd_server, cl->line);
  return (0);
}

void		act_on_recv(char *line, t_client *cl, int mode)
{
  if (mode != 2)
    {
      if (cl->line)
        free(cl->line);
      cl->line = NULL;
      line = recv_cmd(cl->fd_server);
      if (strncmp("230", line, 3) == 0)
        cl->is_connected = true;
      fputs(line, stdout);
    }
  if (line)
    free(line);
}

int		read_line(int fd_sock)
{
  size_t	len;
  ssize_t	readed;
  char		*line;
  t_client	cl;
  int		ret;

  init_struct(&cl, fd_sock);
  line = recv_cmd(fd_sock);
  fputs(line, stdout);
  line = NULL;
  while (cl.is_end == false &&
         (readed = getline(&line, &len, stdin)) != -1)
    {
      cl.line = line;
      ret = my_ptr_func(&cl);
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
  if (read_line(fd_sock) == -1)
    return (-1);
  if (close_socket(fd_sock) == -1)
    return (-1);
  return (0);
}
