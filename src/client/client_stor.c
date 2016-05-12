/*
** client_stor.c for PSU_2015_myftp
**
** Made by	Axel Vencatareddy
** Login	vencat_a
**
** Started on	Thu May 12 19:16:36 2016 Axel Vencatareddy
** Last update	Thu May 12 19:18:13 2016 Axel Vencatareddy
*/

#include "client.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

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

  buf[0] = 0;
  count = 1;
  while (buf[(count == 0 ? 1 : count) - 1] != EOF)
    {
      if ((count = read(file, buf, BUFSIZE)) == -1)
        {
          perror("read()");
          return (-1);
        }
      write(cl->fd_data, buf, count);
    }
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
