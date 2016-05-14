/*
** client_ptr.c for PSU_2015_myftp
**
** Made by	Axel Vencatareddy
** Login	vencat_a
**
** Started on	Sat May 14 00:11:33 2016 Axel Vencatareddy
** Last update	Sat May 14 13:28:13 2016 Axel Vencatareddy
*/

#include "client.h"

void		init_cmp(char *cmp[7])
{
  cmp[0] = "PASV";
  cmp[1] = "PORT";
  cmp[2] = "QUIT";
  cmp[3] = "RETR";
  cmp[4] = "STOR";
  cmp[5] = "LIST";
  cmp[6] = NULL;
}

int		my_ptr_func(t_client *cl)
{
  int		(*ptr[7])(t_client *cl);
  char		*cmp[7];
  int		i;

  ptr[0] = &my_pasv;
  ptr[1] = &my_port;
  ptr[2] = &my_exit;
  ptr[3] = &my_retr;
  ptr[4] = &my_stor;
  ptr[5] = &my_cl_list;
  ptr[6] = NULL;
  init_cmp(cmp);
  i = 0;
  while (i < 6)
    {
      if (strncmp(cl->line, cmp[i], 4) == 0)
        return (ptr[i](cl));
      i++;
    }
  send_msg_client(cl->fd_server, cl->line);
  return (0);
}
