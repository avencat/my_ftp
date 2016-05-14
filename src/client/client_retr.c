/*
** client_retr.c for my_ftp in /home/vencat_a/rendu/PSU/PSU_2015_myftp/src/client
** 
** Made by Axel Vencatareddy
** Login   <vencat_a@epitech.net>
** 
** Started on  Sat May 14 14:11:36 2016 Axel Vencatareddy
** Last update Sat May 14 14:12:03 2016 Axel Vencatareddy
*/

#include "client.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int	my_open_create(char *cmd, int mode, mode_t perm)
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
  if ((file = open(tmp, mode, perm)) == -1)
    perror("open() error");
  free(to_free);
  return (file);
}

int	check_my_retr(t_client *cl)
{
  char	*cmd;

  cmd = recv_cmd(cl->fd_server);
  if (strncmp(cmd, "150", 3) != 0)
    {
      fputs(cmd, stdout);
      free(cmd);
      return (2);
    }
  fputs(cmd, stdout);
  free(cmd);
  return (0);
}

int	my_retr(t_client *cl)
{
  char	buf[BUFSIZE];
  int	file;
  int	count;

  if (cl->is_connected == false || cl->mode == NOPE)
    {
      send_msg_client(cl->fd_server, cl->line);
      return (0);
    }
  if ((file = my_open_create(cl->line, O_RDWR | O_CREAT, 0666)) == -1)
    return (2);
  send_msg_client(cl->fd_server, cl->line);
  if (check_my_retr(cl) == 2)
    return (2);
  while ((count = read(cl->fd_data, buf, BUFSIZE)) > 0)
    write(file, buf, count);
  if (count == -1)
    perror("read() error");
  close(file);
  close_socket(cl->fd_data);
  cl->fd_data = -1;
  cl->mode = NOPE;
  return (0);
}
