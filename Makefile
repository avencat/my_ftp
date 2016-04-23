CC		=  gcc

RM		=  rm -rf

SRCDIR		=  src/
SRCSDIR		=  src/server/
SRCCDIR		=  src/client/

OBJDIR		=  obj/
OBJSDIR		=  obj/server/
OBJCDIR		=  obj/client/

INCDIR		=  inc/
INCSDIR		=  include/server/
INCCDIR		=  include/client/

INCFLAGS	=  -I./$(INCDIR) -I./$(INCCDIR) -I./$(INCSDIR)
CFLAGS		+= -W -Wall -Wextra -Werror $(INCFLAGS)

SERVER		=  serveur
CLIENT		=  client
NAME		=  my_ftp

SRCLIENT	=

SRCSERVER	=  $(SRCSDIR)main.c	\

SRCSERVER	+= $(SRC)

SRCCLIENT	=  $(SRCCDIR)main.c	\

SRCCLIENT	+= $(SRC)

OBJSERVER	=  $(SRCSERVER:$(SRCSDIR)%.c=$(OBJSDIR)%.o)
OBJCLIENT	=  $(SRCCLIENT:$(SRCCDIR)%.c=$(OBJCDIR)%.o)


$(NAME):	   $(CLIENT) $(SERVER)

all:		   $(NAME)

$(OBJCDIR)%.o:	   $(SRCCDIR)%.c
		   @mkdir -p $(OBJCDIR)
		   $(CC) $(CFLAGS) -c $< -o $@

$(OBJSDIR)%.o:	   $(SRCSDIR)%.c
		   @mkdir -p $(OBJSDIR)
		   $(CC) $(CFLAGS) -c $< -o $@

$(CLIENT):	   $(OBJCLIENT)
		   $(CC) $(CFLAGS) -o $(CLIENT) $(OBJCLIENT)

$(SERVER):  	   $(OBJSERVER)
		   $(CC) $(CFLAGS) -o $(SERVER) $(OBJSERVER)

clean:
		   $(RM) $(OBJSERVER)
		   $(RM) $(OBJCLIENT)

fclean:		   clean
		   $(RM) $(SERVER)
		   $(RM) $(CLIENT)

re:		   fclean all

.PHONY:	   	   all clean fclean re
