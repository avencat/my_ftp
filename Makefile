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
CFLAGS		+= -W -Wall -Wextra -Werror $(INCFLAGS)

SERVER		=  serveur
CLIENT		=  client
NAME		=  my_ftp

SRC		=  $(SRCDIR)socket.c	\

SRCSERVER	=  $(SRCSERVERDIR)main.c	\
		   $(OBJ)

SRCCLIENT	=  $(SRCCLIENTDIR)main.c	\
		   $(OBJ)

OBJ		=  $(SRC:$(SRCDIR)%.c=$(OBJDIR)%.o)
OBJCLIENT	=  $(SRCCLIENT:$(SRCCLIENTDIR)%.c=$(OBJCLIENTDIR)%.o)
OBJSERVER	=  $(SRCSERVER:$(SRCSERVERDIR)%.c=$(OBJSERVERDIR)%.o)


$(NAME):	   $(OBJ) msg $(CLIENT) $(SERVER)

all:		   $(NAME)

msg:
		   @echo -e "\033[33mCommons Compiled\033[00m"

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
