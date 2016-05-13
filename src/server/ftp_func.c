/*
** ftp_func.c for PSU_2015_myftp
**
** Made by	Axel Vencatareddy
** Login	vencat_a
**
** Started on	Fri May 13 11:48:29 2016 Axel Vencatareddy
** Last update	Fri May 13 11:49:37 2016 Axel Vencatareddy
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

int	my_list(t_ptr *struc)
{
  int	tmp;

  if (struc->is_connected == false)
    send_msg(struc->client_fd, "530 Please login with USER and PASS.\r\n");
  else if (struc->mode == NOPE)
    send_msg(struc->client_fd, "425 Use PORT or PASV first.\r\n");
  else
    {
      send_msg(struc->client_fd, "150 Opening ASCII mode data connection.\r\n");
      struc->mode = NOPE;
      tmp = dup(1);
      dup2(struc->data_fd, 1);
      system("ls -l | grep -v ^d | grep -v ^total");
      dup2(tmp, 1);
      close(tmp);
      close_socket(struc->data_fd);
      send_msg(struc->client_fd, "226 Transfer complete.\r\n");
    }
  return (0);
}
