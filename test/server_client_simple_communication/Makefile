##
## Makefile for Test in /home/alexmog/projets/LibNet/test/server_client_simple_communication
## 
## Made by Moghrabi Alexandre
## Login   <alexandre.moghrabi@epitech.eu>
## 
## Started on  Thu Nov 20 20:19:45 2014 Moghrabi Alexandre
## Last update Thu Nov 20 20:31:15 2014 Moghrabi Alexandre
##

NAMEC=	client

NAMES=	server

SRCC=	main2.cpp

SRCS=	main.cpp

OBJC=	$(SRCC:.cpp=.o)

OBJS=	$(SRCS:.cpp=.o)

CXX=	g++

RM=	rm -rf

LDFLAGS=	-lmognetwork -lpthread

CXXFLAGS=	

all:	$(NAMEC) $(NAMES)

$(NAMEC):	$(OBJC)
		$(CXX) -o $(NAMEC) $(LDFLAGS) $(OBJC) 

$(NAMES):	$(OBJS)
		$(CXX) -o $(NAMES) $(LDFLAGS) $(OBJS)

debug:		CXXFLAGS += -g3
debug:		all

clean:
		$(RM) $(OBJS) $(OBJC)

fclean:		clean
		$(RM) $(NAMES) $(NAMEC)

re:		fclean all

.PHONY:		debug clean fclean re all