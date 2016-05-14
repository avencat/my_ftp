/*
** ftp_dir.c for my_ftp in /home/vencat_a/rendu/PSU/PSU_2015_myftp/src/server
** 
** Made by Axel Vencatareddy
** Login   <vencat_a@epitech.net>
** 
** Started on  Sat May 14 14:13:13 2016 Axel Vencatareddy
** Last update Sat May 14 14:13:15 2016 Axel Vencatareddy
*/

#include "server.h"
#include <linux/limits.h>

int	my_pwd(t_ptr *struc)
{
  char	str[PATH_MAX + 9];

  if (!struc->tab || struc->is_connected == false)
    send_msg(struc->client_fd, "530 Please login with USER and PASS.\r\n");
  else
    {
      memset(struc->pwd_to_free, 0, PATH_MAX);
      getcwd(struc->pwd_to_free, PATH_MAX);
      sprintf(str, "257 \"%s\"\r\n",
              (my_strlen(struc->pwd_to_free) > 0 ? struc->pwd_to_free : "/"));
      send_msg(struc->client_fd, str);
    }
  return (0);
}

void	change_pwd(t_ptr *struc)
{
  struc->pwd = struc->pwd_to_free + my_strlen(struc->root_dir);
  if (struc->pwd[0] == 0)
    struc->pwd[0] = '/';
}

int	my_cwd(t_ptr *struc)
{
  if (struc->is_connected == false)
    send_msg(struc->client_fd, "530 Please login with USER and PASS.\r\n");
  else if (!struc->tab || !struc->tab[1])
    send_msg(struc->client_fd, "550 Failed to change directory.\r\n");
  else
    {
      if (chdir(struc->tab[1]) == -1)
        send_msg(struc->client_fd, "550 Failed to change directory.\r\n");
      else
        {
          memset(struc->pwd_to_free, 0, PATH_MAX + 1);
          if (getcwd(struc->pwd_to_free, PATH_MAX) == NULL)
            {
              perror("getcwd() error");
              return (-1);
            }
          if (my_strlen(struc->root_dir) > my_strlen(struc->pwd_to_free))
            if (chdir(struc->root_dir) == -1)
              return (send_msg(struc->client_fd, "550 Failed to change dir\
ectory.\r\n"));
          send_msg(struc->client_fd, "250 Directory successfully changed.\r\n");
          change_pwd(struc);
        }
    }
  return (0);
}

int	my_cdup(t_ptr *struc)
{
  if (struc->is_connected == false)
    send_msg(struc->client_fd, "530 Please login with USER and PASS.\r\n");
  else
    {
      if (chdir("..") == -1)
        send_msg(struc->client_fd, "550 Failed to change directory.\r\n");
      else
        {
          if (getcwd(struc->pwd_to_free, PATH_MAX) == NULL)
            {
              perror("getcwd() error");
              return (-1);
            }
          if (my_strlen(struc->root_dir) > my_strlen(struc->pwd_to_free))
            if (chdir(struc->root_dir) == -1)
              return (send_msg(struc->client_fd, "550 Failed to change dir\
ectory.\r\n"));
          send_msg(struc->client_fd, "200 Directory successfully changed.\r\n");
          change_pwd(struc);
        }
    }
  return (0);
}
