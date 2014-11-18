##
## Makefile for Makefile in 
## 
## Made by Moghrabi Alexandre
## Login   <alexmog@epitech.net>
## 
## Started on  Fri Jun  6 11:16:50 2014 Moghrabi Alexandre
## Last update Tue Nov 18 10:22:47 2014 Moghrabi Alexandre
##

NAME=	mognetwork

LIBNAME=lib$(NAME).so

INCLIB=	$(NAME)

ALIBNAME=lib$(NAME).a

SRCDIR=	./src/

SRC=	$(SRCDIR)CondVar.cpp		\
	$(SRCDIR)IpAddress.cpp		\
	$(SRCDIR)Mutex.cpp		\
	$(SRCDIR)Selector.cpp		\
	$(SRCDIR)Socket.cpp		\
	$(SRCDIR)TcpASIODatas.cpp	\
	$(SRCDIR)TcpASIOListener.cpp	\
	$(SRCDIR)TcpASIOWriter.cpp	\
	$(SRCDIR)TcpSocket.cpp		\
	$(SRCDIR)Thread.cpp		\
	$(SRCDIR)UnixSocket.cpp		\
	$(SRCDIR)WinSocket.cpp		\
	$(SRCDIR)TcpServerSocket.cpp	\
	$(SRCDIR)TcpASIOServer.cpp	\
	$(SRCDIR)Packet.cpp


OBJS=	$(SRC:.cpp=.o)

RM=	rm -rf

CXX=	g++

AR=	ar rs

CXXFLAGS=	-Wall -Werror -Wextra -I include -ansi -pedantic
LDFLAGS=	

all:		$(NAME)

$(NAME):	$(OBJS)
		$(AR) $(ALIBNAME) $(LDFLAGS) $(OBJS)

debug:		CXXFLAGS += -g3
debug:		$(NAME)

clean:
		$(RM) $(OBJS)

fclean:		clean
		$(RM) $(ALIBNAME)

re:		fclean all

.PHONY:		all debug clean fclean re
