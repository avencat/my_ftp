/*
** ftp_cwd_func.c for PSU_2015_myftp
**
** Made by	Axel Vencatareddy
** Login	vencat_a
**
** Started on	Mon May 09 15:59:05 2016 Axel Vencatareddy
** Last update	Tue May 10 23:38:58 2016 Axel Vencatareddy
*/

#include "server.h"
#include <linux/limits.h>

int	my_pwd(t_ptr *struc)
{
  if (!struc->tab || struc->is_connected == false)
    send_msg(struc->client_fd, "530 Please login with USER and PASS.\r\n");
  else
    {
      send_msg(struc->client_fd, "257 \"");
      if (my_strlen(struc->pwd) > 0)
        send_msg(struc->client_fd, struc->pwd);
      else
        send_msg(struc->client_fd, "/");
      send_msg(struc->client_fd, "\"\r\n");
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
  my_free_tab(struc->tab);
  struc->tab = malloc(sizeof(char *) * 3);
  struc->tab[0] = strdup("CWD");
  struc->tab[1] = strdup("..");
  struc->tab[2] = NULL;
  return (my_cwd(struc));
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
      tmp = dup(0);
      dup2(struc->data_fd, 0);
      system("ls -l | grep -v ^d | grep -v ^total");
      dup2(tmp, 0);
      send_msg(struc->client_fd, "226 Transfer complete.\r\n");
    }
  return (0);
}
