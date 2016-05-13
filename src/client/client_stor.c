/*
** client_stor.c for PSU_2015_myftp
**
** Made by	Axel Vencatareddy
** Login	vencat_a
**
** Started on	Thu May 12 19:16:36 2016 Axel Vencatareddy
** Last update	Sat May 14 00:15:22 2016 Axel Vencatareddy
*/

#include "client.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int	my_open(char *cmd, int mode)
{
  int	file;
  char	*tmp;
  char	*to_free;
  int	i;

  to_free = strdup(cmd);
  tmp = strchr(to_free, ' ') + 1;
  i = 0;
  while (tmp && tmp[i])
    {
      if (tmp[i] == '\r' || tmp[i] == '\n')
        tmp[i] = '\0';
      i++;
    }
  if ((file = open(tmp, mode)) == -1)
    perror("open() error");
  free(to_free);
  return (file);
}

int	check_my_stor(t_client *cl)
{
  char	*cmd;

  cmd = recv_cmd(cl->fd_server);
  if (strncmp("150", cmd, 3) != 0)
    {
      fputs(cmd, stdout);
      free(cmd);
      return (2);
    }
  fputs(cmd, stdout);
  free(cmd);
  return (0);
}

int	my_stor_end(t_client *cl, int file)
{
  char	buf[BUFSIZE];
  int	count;

  while ((count = read(file, buf, BUFSIZE)) > 0)
    {
      write(cl->fd_data, buf, count);
    }
  if (count == -1)
    {
      close(file);
      perror("read()");
      return (-1);
    }
  close(file);
  return (0);
}

int	my_stor(t_client *cl)
{
  int	file;

  if (cl->is_connected == false || cl->mode == NOPE)
    return (send_msg(cl->fd_server, cl->line));
  if ((file = my_open(cl->line, O_RDONLY)) == -1)
    {
      fprintf(stderr, "Client: File doesn't exist or is busy.\
 Not sending cmd.\n");
      return (2);
    }
  send_msg(cl->fd_server, cl->line);
  if (check_my_stor(cl) == 2)
    return (2);
  if (my_stor_end(cl, file) == -1)
    return (-1);
  close_socket(cl->fd_data);
  cl->fd_data = -1;
  cl->mode = NOPE;
  return (0);
}
