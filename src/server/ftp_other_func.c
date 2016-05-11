/*
** ftp_other_func.c for PSU_2015_myftp
**
** Made by	Axel Vencatareddy
** Login	vencat_a
**
** Started on	Mon May 09 10:13:12 2016 Axel Vencatareddy
** Last update	Wed May 11 15:52:20 2016 Axel Vencatareddy
*/

#include "functions_ptr.h"

int	my_help(t_ptr *struc)
{
  if (!struc->tab || struc->is_connected == false)
    send_msg(struc->client_fd, "530 Permission denied.\r\n");
  else
    send_msg(struc->client_fd, "214 The following commands are recognized.\n \
CDUP CWD  DELE HELP LIST NOOP PASS PASV PORT PWD  QUIT RETR STOR USER\n\
214 Help OK.\r\n");
  return (0);
}

int	my_noop(t_ptr *struc)
{
  if (!struc->tab || struc->is_connected == false)
    send_msg(struc->client_fd, "530 Please login with USER and PASS.\r\n");
  else
    send_msg(struc->client_fd, "200 NOOP ok.\r\n");
  return (0);
}

int	my_stor(t_ptr *struc)
{
  char	buf[BUFSIZE];
  FILE	*file;
  int	count;

  if (struc->is_connected == false)
    send_msg(struc->client_fd, "530 Please login with USER and PASS.\r\n");
  else if (struc->mode == NOPE)
    send_msg(struc->client_fd, "425 Use PORT or PASV first.\r\n");
  else if (!struc->tab[1] || !struc->tab[2])
    send_msg(struc->client_fd, "550 Permission Denied.\r\n");
  else
    {
      if ((file = fopen(struc->tab[1], "r")) == NULL)
        return (send_msg(struc->client_fd, "450 Permission denied.\r\n"));
      send_msg(struc->client_fd, "150 Opening ASCII mode data connection.\r\n");
      while ((count = read(struc->data_fd, buf, BUFSIZE - 1)) != 0)
        {
          buf[count] = '\0';
          fputs(buf, file);
        }
      close_socket(struc->data_fd);
      struc->mode = NOPE;
      send_msg(struc->client_fd, "226 Transfer complete.\r\n");
    }
  return (0);
}

int	my_retr(t_ptr *struc)
{
  char	buf[BUFSIZE];
  FILE	*file;

  if (struc->is_connected == false)
    send_msg(struc->client_fd, "530 Please login with USER and PASS.\r\n");
  else if (struc->mode == NOPE)
    send_msg(struc->client_fd, "425 Use PORT or PASV first.\r\n");
  else if (!struc->tab[1] || !struc->tab[2])
    send_msg(struc->client_fd, "550 Permission Denied.\r\n");
  else
    {
      if ((file = fopen(struc->tab[1], "r")) == NULL)
        return (send_msg(struc->client_fd, "450 Permission denied.\r\n"));
      send_msg(struc->client_fd, "150 Opening ASCII mode data connection.\r\n");
      while (fgets(buf, BUFSIZE - 1, file))
        send_msg(struc->data_fd, buf);
      close_socket(struc->data_fd);
      struc->mode = NOPE;
      send_msg(struc->client_fd, "226 Transfer complete.\r\n");
    }
  return (0);
}
