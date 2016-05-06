/*
** functions_ptr.c for PSU_2015_myftp
**
** Made by	Axel Vencatareddy
** Login	vencat_a
**
** Started on	Fri May 06 15:16:12 2016 Axel Vencatareddy
** Last update	Fri May 06 19:08:51 2016 Axel Vencatareddy
*/

#include "functions_ptr.h"

int	my_ptr_func(int (*ptr[14])(t_ptr *), char *ptr_name[14], t_ptr *struc)
{
  int	i;

  i = 0;
  while (i < 14 && struc->tab)
    {
      if (ptr[i] && strncmp(ptr_name[i], struc->tab[0],
                            my_strlen(ptr_name[i])) == 0)
        return (ptr[i](struc));
      i++;
    }
  if (struc->is_connected == false && my_strlen(struc->tab[0]) > 0)
    return (send_msg(struc->client_fd, "530 Permission denied.\r\n"));
  else if (my_strlen(struc->tab[0]) > 0)
    return (send_msg(struc->client_fd, "500 Unknown command.\r\n"));
  return (0);
}

void	init_functions_ptr(char *tab[14])
{
  tab[0] = "USER";
  tab[1] = "PASS";
  tab[2] = "CWD";
  tab[3] = "CDUP";
  tab[4] = "QUIT";
  tab[5] = "DELE";
  tab[6] = "PWD";
  tab[7] = "PASV";
  tab[8] = "PORT";
  tab[9] = "HELP";
  tab[10] = "NOOP";
  tab[11] = "RETR";
  tab[12] = "STOR";
  tab[13] = "LIST";
}

int	functions_ptr(t_ptr *struc)
{
  int	(*ptr[14])(t_ptr *);
  char	*ptr_name[14];

  init_functions_ptr(ptr_name);
  ptr[0] = &my_user;
  ptr[1] = &my_pass;
  // ptr[2] = &my_cwd;
  // ptr[3] = &my_cdup;
  ptr[4] = &my_quit;
  // ptr[5] = &my_dele;
  // ptr[6] = &my_pwd;
  // ptr[7] = &my_pasv;
  // ptr[8] = &my_port;
  // ptr[9] = &my_help;
  // ptr[10] = &my_noop;
  // ptr[11] = &my_retr;
  // ptr[12] = &my_stor;
  // ptr[13] = &my_list;
  return (my_ptr_func(ptr, ptr_name, struc));
}
