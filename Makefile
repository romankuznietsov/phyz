CC = g++
WARN = -pedantic -Wall -Wextra

LGLUT = -lGL -lGLU -lglut

SRCS = $(wildcard src/*.cpp)
OBJS = $(patsubst src/%.cpp, obj/%.o, $(SRCS))

gravitality : $(OBJS)
	$(CC) $(OBJS) $(LGLUT) -o app

obj/%.o : src/%.cpp
	$(CC) -c $(WARN) $< -o $@

clean :
	-rm -f obj/*.o
	-rm -f app
