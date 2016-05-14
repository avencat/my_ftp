/*
** server.h for my_ftp in /home/vencat_a/rendu/PSU/PSU_2015_myftp/include/server
** 
** Made by Axel Vencatareddy
** Login   <vencat_a@epitech.net>
** 
** Started on  Sat May 14 14:17:53 2016 Axel Vencatareddy
** Last update Sat May 14 14:17:54 2016 Axel Vencatareddy
*/

#ifndef SERVER_H_
# define SERVER_H_

# define BUFSIZE	1024

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <pthread.h>
# include "socket_prot.h"
# include "my_string_prot.h"

typedef enum { false, true } bool;
typedef enum { PASV, ACTV, NOPE } data_mode;

typedef struct	s_ptr
{
  char		**tab;
  int		client_fd;
  int		server_fd;
  char		*user;
  bool		is_connected;
  bool		end;
  char		*pwd;
  char		*pwd_to_free;
  char		*root_dir;
  data_mode	mode;
  int		data_fd;
  int		data_socket;
  int		data_port;
}		t_ptr;

int		functions_ptr(t_ptr *);
char		*get_current_dir_name();
void		my_free_tab(char **);
void		init_struc(t_ptr *, int, int, char *);
void		free_struct(t_ptr *);
void		my_null_cmd(t_ptr *);

#endif /* !SERVER_H_ */
