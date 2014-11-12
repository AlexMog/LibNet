##
## Makefile for Makefile in 
## 
## Made by Moghrabi Alexandre
## Login   <alexmog@epitech.net>
## 
## Started on  Fri Jun  6 11:16:50 2014 Moghrabi Alexandre
## Last update Wed Nov 12 10:33:51 2014 Moghrabi Alexandre
##

NAME=	mognetwork

LIBNAME=lib$(NAME).so

INCLIB=	$(NAME)

SRCDIR=	./src/

SRC=	$(SRCDIR)IpAddress.cpp		\
	$(SRCDIR)UnixSocket.cpp		\
	$(SRCDIR)Socket.cpp		\
	$(SRCDIR)TcpSocket.cpp		\
	$(SRCDIR)WinSocket.cpp		\
	$(SRCDIR)Selector.cpp		\
	$(SRCDIR)Thread.cpp		\
	$(SRCDIR)Mutex.cpp		\
	$(SRCDIR)CondVar.cpp

OBJS=	$(SRC:.cpp=.o)

RM=	rm -rf

CXX=	g++

AR=	ar rs

CXXFLAGS=	-Wall -Werror -Wextra -I include
LDFLAGS=	

all:		$(NAME)

$(NAME):	$(OBJS)
		$(AR) $(NAME) $(LDFLAGS) $(OBJS)

debug:		CXXFLAGS += -g3
debug:		$(NAME)

clean:
		$(RM) $(OBJS)

fclean:		clean
		$(RM) $(NAME)

re:		fclean all

.PHONY:		all debug clean fclean re
