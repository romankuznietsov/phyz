CC = g++
WARN = -pedantic -Wall -Wextra

LGLUT = -lglut -lGLU -lGL

SRCS = $(wildcard src/*.cpp)
OBJS = $(patsubst src/%.cpp, obj/%.o, $(SRCS))

gravitality : $(OBJS)
	$(CC) $(LGLUT) $(OBJS) -o app

obj/%.o : src/%.cpp
	$(CC) -c $(WARN) $< -o $@

clean :
	-rm -f obj/*.o
	-rm -f app
