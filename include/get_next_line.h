/*
** shell.h for my_ftp in /home/vencat_a/rendu/PSU/PSU_2015_myftp
**
** Made by Axel Vencatareddy
** Login   <vencat_a@epitech.net>
**
** Started on  Sat May 14 12:31:43 2016 Axel Vencatareddy
** Last update	Sat May 14 12:48:23 2016 Axel Vencatareddy
*/

#ifndef GET_NEXT_LINE_H_
# define GET_NEXT_LINE_H_

/*
** Include
*/

# include <stdlib.h>
# include <unistd.h>
# include <string.h>

/*
** Macro
*/

# define BUFSIZ 1024
# define FALSE (-1)
# define TRUE (0)
# define UNUSED __attribute__((unused))

/*
** Structure for get_next_line
*/

typedef struct	s_gnl
{
  int		pos;
  char		*line;
  char		ctrl_d;
  int		i;
  int		error;
  int		fd;
}		t_gnl;

int	my_strlen(char *);
int	my_error(char *, int);

#endif /* !GET_NEXT_LINE_H_ */
