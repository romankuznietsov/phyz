CC = g++
WARN = -pedantic -Wall -Wextra

LGLUT = -lGL -lGLU -lglut

SRCS = $(wildcard src/*.cpp)
OBJS = $(patsubst src/%.cpp, obj/%.o, $(SRCS))

phyz : $(OBJS)
	$(CC) $(OBJS) $(LGLUT) -o phyz

obj/%.o : src/%.cpp
	mkdir obj -p
	$(CC) -c $(WARN) $< -o $@

clean :
	-rm -f obj/*.o
	-rm -f phyz
