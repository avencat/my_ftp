/*
** ftp_connect.c for my_ftp in /home/vencat_a/rendu/PSU/PSU_2015_myftp/src/server
** 
** Made by Axel Vencatareddy
** Login   <vencat_a@epitech.net>
** 
** Started on  Sat May 14 14:13:00 2016 Axel Vencatareddy
** Last update Sat May 14 14:13:00 2016 Axel Vencatareddy
*/

#include "functions_ptr.h"

int	my_user(t_ptr *struc)
{
  if (!struc->tab || !struc->tab[1] || my_strlen(struc->tab[1]) == 0)
    send_msg(struc->client_fd, "530 Permission denied.\r\n");
  else
    {
      if (struc->user)
        free(struc->user);
      struc->user = strdup(struc->tab[1]);
      send_msg(struc->client_fd, "331 Please specify the password.\r\n");
    }
  return (0);
}

int	my_pass(t_ptr *struc)
{
  if (struc->is_connected == true)
    send_msg(struc->client_fd, "230 Already logged in.\r\n");
  else if (!struc->tab || !struc->user)
    send_msg(struc->client_fd, "503 Login with USER first.\r\n");
  else if (strcmp(struc->user, "Anonymous") == 0)
    {
      send_msg(struc->client_fd, "230 Login successful.\r\n");
      struc->is_connected = true;
    }
  else
    {
      send_msg(struc->client_fd, "530 Login incorrect.\r\n");
      if (struc->user)
        free(struc->user);
      struc->user = NULL;
    }
  return (0);
}

int	my_quit(t_ptr *struc)
{
  send_msg(struc->client_fd, "221 Goodbye.\r\n");
  struc->end = true;
  shutdown(struc->client_fd, 2);
  return (0);
}

int	my_dele(t_ptr *struc)
{
  if (struc->is_connected == false)
    send_msg(struc->client_fd, "530 Please login with USER and PASS.\r\n");
  else if (!struc->tab[1])
    send_msg(struc->client_fd, "550 Permission denied.\r\n");
  else
    {
      if (remove(struc->tab[1]) == -1)
        send_msg(struc->client_fd, "550 Permission denied.\r\n");
      else
        send_msg(struc->client_fd, "250 File deleted.\r\n");
    }
  return (0);
}

void		my_null_cmd(t_ptr *struc)
{
  if (struc->is_connected == false)
    send_msg(struc->client_fd, "530 Please login with USER and PASS.\r\n");
  else
    send_msg(struc->client_fd, "500 Unknown Command.\r\n");
}
