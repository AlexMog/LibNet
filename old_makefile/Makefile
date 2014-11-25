##
## Makefile for Makefile in 
## 
## Made by Moghrabi Alexandre
## Login   <alexmog@epitech.net>
## 
## Started on  Fri Jun  6 11:16:50 2014 Moghrabi Alexandre
## Last update Mon Nov 24 17:58:49 2014 Moghrabi Alexandre
##

NAME=	mognetwork

LIBNAME=lib$(NAME).so

INCLIB=	$(NAME)

ALIBNAME=lib$(NAME).a

BINDIR=./bin/

SRCDIR=	./src/

INCDIR= ./include/

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

CP=	cp -rf

CXXFLAGS=	-Wall -Werror -Wextra -I $(INCDIR) -ansi -pedantic -fPIC

LDFLAGS=	

all:		shared static

$(BINDIR)$(LIBNAME):	$(OBJS)
		mkdir -p bin
		$(CXX) --shared -o $(BINDIR)$(LIBNAME) $(LDFLAGS) $(OBJS)

$(BINDIR)$(ALIBNAME):	$(OBJS)
		mkdir -p bin
		$(AR) $(BINDIR)$(ALIBNAME) $(LDFLAGS) $(OBJS)

debug-shared:	CXXFLAGS += -g3
debug-shared:	shared
debug-static:	CXXFLAGS += -g3
debug-static:	static

static:		$(BINDIR)$(ALIBNAME)

shared:		$(BINDIR)$(LIBNAME)

clean:
		$(RM) $(OBJS)

fclean:		clean
		$(RM) $(BINDIR)$(LIBNAME)
		$(RM) $(BINDIR)$(ALIBNAME)

re:		fclean all

install:
		$(CP) $(BINDIR)$(LIBNAME) /usr/local/lib/
		mkdir -p /usr/local/include/$(NAME)
		$(CP) $(INCDIR)/* /usr/local/include/$(NAME)/
		ldconfig

uninstall:
		$(RM) /usr/local/lib/$(LIBNAME)
		$(RM) /usr/local/include/$(NAME)
		ldconfig

.PHONY:		all debug-static debug-shared clean fclean re static shared install uninstall
