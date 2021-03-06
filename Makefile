##
## Makefile for my_ftp in /home/vencat_a/rendu/PSU/PSU_2015_myftp
##
## Made by Axel Vencatareddy
## Login   <vencat_a@epitech.net>
##
## Started on  Sat May 14 00:17:23 2016 Axel Vencatareddy
## Last update Jul May 14 12:49:00 2016 Axel Vencatareddy
##

CC		=  gcc

RM		=  rm -rf

SRCDIR		=  src/
SRCSERVERDIR	=  src/server/
SRCCLIENTDIR	=  src/client/

OBJDIR		=  obj/
OBJSERVERDIR	=  obj/server/
OBJCLIENTDIR	=  obj/client/

INCDIR		=  include/
INCSERVERDIR	=  include/server/
INCCLIENTDIR	=  include/client/

INCFLAGS	=  -I./$(INCDIR) -I./$(INCCLIENTDIR) -I./$(INCSERVERDIR)
CFLAGS		+= -W -Wall -Wextra -Werror $(INCFLAGS) -g

SERVER		=  server
CLIENT		=  client
NAME		=  my_ftp

SRC		=  $(SRCDIR)socket.c			\
		   $(SRCDIR)transmission.c		\
		   $(SRCDIR)string.c			\
		   $(SRCDIR)error.c			\
		   $(SRCDIR)get_next_line.c		\

SRCSERVER	=  $(SRCSERVERDIR)server.c		\
		   $(SRCSERVERDIR)ftp_connect.c		\
		   $(SRCSERVERDIR)ftp_dir.c		\
		   $(SRCSERVERDIR)ftp_func.c		\
		   $(SRCSERVERDIR)ftp_pasv.c		\
		   $(SRCSERVERDIR)ftp_port.c		\
		   $(SRCSERVERDIR)ftp_retr.c		\
		   $(SRCSERVERDIR)ftp_stor.c		\
		   $(SRCSERVERDIR)ftp_sockets.c		\
		   $(SRCSERVERDIR)functions_ptr.c	\
		   $(SRCSERVERDIR)struct.c		\
		   $(OBJ)

SRCCLIENT	=  $(SRCCLIENTDIR)client.c		\
		   $(SRCCLIENTDIR)struct.c		\
		   $(SRCCLIENTDIR)client_ptr.c		\
		   $(SRCCLIENTDIR)client_port.c		\
		   $(SRCCLIENTDIR)client_pasv.c		\
		   $(SRCCLIENTDIR)client_func.c		\
		   $(SRCCLIENTDIR)client_stor.c		\
		   $(SRCCLIENTDIR)client_retr.c		\
		   $(SRCCLIENTDIR)client_pasv_func.c	\
		   $(OBJ)

OBJ		=  $(SRC:$(SRCDIR)%.c=$(OBJDIR)%.o)
OBJCLIENT	=  $(SRCCLIENT:$(SRCCLIENTDIR)%.c=$(OBJCLIENTDIR)%.o)
OBJSERVER	=  $(SRCSERVER:$(SRCSERVERDIR)%.c=$(OBJSERVERDIR)%.o)


$(NAME):	   $(OBJ) $(CLIENT) $(SERVER)

all:		   $(NAME)

$(OBJDIR)%.o:	   $(SRCDIR)%.c
		   @mkdir -p $(OBJDIR)
		   @mkdir -p $(OBJCLIENTDIR)
		   @mkdir -p $(OBJSERVERDIR)
		   @echo -e "Compiling $<"
		   @$(CC) $(CFLAGS) -c $< -o $@

$(OBJCLIENTDIR)%.o:$(SRCCLIENTDIR)%.c
		   @echo -e "Compiling $<"
		   @$(CC) $(CFLAGS) -c $< -o $@

$(OBJSERVERDIR)%.o:$(SRCSERVERDIR)%.c
		   @echo -e "Compiling $<"
		   @$(CC) $(CFLAGS) -c $< -o $@

$(CLIENT):	   $(OBJCLIENT)
		   @$(CC) $(CFLAGS) -o $(CLIENT) $(OBJCLIENT)
		   @echo -e "\033[33mClient Compiled\033[00m"

$(SERVER):  	   $(OBJSERVER)
		   @$(CC) $(CFLAGS) -o $(SERVER) $(OBJSERVER)
		   @echo -e "\033[33mServer Compiled\033[00m"

clean:
		   @echo -e "\033[31mRemoving Objects\033[00m"
		   @$(RM) $(OBJSERVER)
		   @$(RM) $(OBJCLIENT)
		   @$(RM) $(OBJDIR)

fclean:		   clean
		   @echo -e "\033[31mRemoving Client & Serveur\033[00m"
		   @$(RM) $(SERVER)
		   @$(RM) $(CLIENT)

re:		   fclean all

.PHONY:	   	   all clean fclean re
