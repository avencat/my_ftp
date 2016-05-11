/*
** functions_ptr.h for PSU_2015_myftp
**
** Made by	Axel Vencatareddy
** Login	vencat_a
**
** Started on	Fri May 06 15:17:23 2016 Axel Vencatareddy
** Last update	Wed May 11 13:09:17 2016 Axel Vencatareddy
*/

#ifndef FUNCTIONS_PTR_H_
# define FUNCTIONS_PTR_H_

# include "server.h"

int	my_user(t_ptr *);
int	my_pass(t_ptr *);
int	my_cwd(t_ptr *);
int	my_cdup(t_ptr *);
int	my_quit(t_ptr *);
int	my_dele(t_ptr *);
int	my_pwd(t_ptr *);
int	my_pasv(t_ptr *);
int	my_port(t_ptr *);
int	my_help(t_ptr *);
int	my_noop(t_ptr *);
int	my_retr(t_ptr *);
int	my_stor(t_ptr *);
int	my_list(t_ptr *);

#endif /* !FUNCTIONS_PTR_H_ */
