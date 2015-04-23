##
## Makefile for Test in /home/alexmog/projets/LibNet/test/server_client_simple_communication
## 
## Made by Moghrabi Alexandre
## Login   <alexandre.moghrabi@epitech.eu>
## 
## Started on  Thu Nov 20 20:19:45 2014 Moghrabi Alexandre
## Last update Tue Apr 21 15:17:44 2015 Moghrabi Alexandre
##

NAMEC=	client

NAMES=	server

SRCC=	main2.cpp

SRCS=	main.cpp

OBJC=	$(SRCC:.cpp=.o)

OBJS=	$(SRCS:.cpp=.o)

CXX=	g++

RM=	rm -rf

LDFLAGS=	-lmognetwork
ifneq ($(OS),Windows_NT)
LDFLAGS += -lpthread
endif

CXXFLAGS=	-g3

all:	$(NAMEC) $(NAMES)

$(NAMEC):	$(OBJC)
		$(CXX) -o $(NAMEC) $(OBJC) $(LDFLAGS)

$(NAMES):	$(OBJS)
		$(CXX) -o $(NAMES) $(OBJS) $(LDFLAGS)

debug:		CXXFLAGS += -g3
debug:		all

clean:
		$(RM) $(OBJS) $(OBJC)

fclean:		clean
ifneq ($(OS),Windows_NT)
		$(RM) $(NAMES) $(NAMEC)
else
		$(RM) $(NAMES).exe $(NAMEC).exe
endif

re:		fclean all

.PHONY:		debug clean fclean re all