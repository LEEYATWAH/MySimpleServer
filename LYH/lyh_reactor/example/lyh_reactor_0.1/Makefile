CXX=g++
CFLAGS=-g -O2 -Wall -fPIC -Wno-deprecated 

INC=-I../../include
LIB=-L../../lib -llreactor 
OBJS = $(addsuffix .o, $(basename $(wildcard *.cc)))

all:
	$(CXX) -o lyh_reactor $(CFLAGS)  lyh_reactor.cpp $(INC) $(LIB)

clean:
	-rm -f *.o lyh_reactor