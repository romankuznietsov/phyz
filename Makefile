CC = g++
WARN = -pedantic -Wall -Wextra

BOOST_PATH = /home/roman/projects/boost
CBOOST = -I$(BOOST_PATH)
LBOOST = -L$(BOOST_PATH)/stage/lib

LGLUT = -lglut -lGLU -lGL

SRCS = $(wildcard src/*.cpp)
OBJS = $(patsubst src/%.cpp, obj/%.o, $(SRCS))

gravitality : $(OBJS)
	$(CC) $(LBOOST) $(LGLUT) $(OBJS) -o app

obj/%.o : src/%.cpp
	$(CC) -c $(WARN) $(CBOOST) $< -o $@

clean :
	-rm -f obj/*.o
	-rm -f app
