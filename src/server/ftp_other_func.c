/*
** ftp_other_func.c for PSU_2015_myftp
**
** Made by	Axel Vencatareddy
** Login	vencat_a
**
** Started on	Mon May 09 10:13:12 2016 Axel Vencatareddy
** Last update	Tue May 10 21:33:53 2016 Axel Vencatareddy
*/

#include "functions_ptr.h"

int	my_help(t_ptr *struc)
{
  if (!struc->tab || struc->is_connected == false)
    send_msg(struc->client_fd, "530 Permission denied.\r\n");
  else
    send_msg(struc->client_fd, "214-The following commands are recognized.\n \
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
