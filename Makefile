CC = g++
WARN = -pedantic -Wall -Wextra

PACKAGES = boost
CFLAGS =  `pkg-config --cflags $(PACKAGES)`
LFLAGS =  `pkg-config --libs $(PACKAGES)`
LGLUT = -lglut -lGLU -lGL

SRCS = $(wildcard src/*.cpp)
OBJS = $(patsubst src/%.cpp, obj/%.o, $(SRCS))

gravitality : $(OBJS)
	$(CC) $(LFLAGS) $(LGLUT) $(OBJS) -o app

obj/%.o : src/%.cpp
	$(CC) -c $(WARN) $(CFLAGS) $< -o $@

clean :
	-rm -f obj/*.o
	-rm -f gravitality
