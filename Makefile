CXX = g++
CXXFLAGS = -Wall

OBJS = main.o \
	command.o \
	stream.o \
	tools.o

default: cubescript-standalone

cubescript-standalone: $(OBJS)
	$(CXX) $(CXXFLAGS) -o cubescript-standalone $(OBJS)
	
%.o: %.cpp
	$(CXX) -c -o $@ $<

clean: 
	rm -f $(OBJS) cubescript-standalone

##############################################
main.o: cube.h tools.h iengine.h command.h
command.o: cube.h command.h tools.h iengine.h
stream.o: cube.h tools.h
tools.o: tools.h
