APP_NAME = phyz

CXX = g++
CXXFLAGS = -pedantic -Wall -Wextra
LDFLAGS = -lGL -lGLU -lglut

SRCS = $(wildcard src/*.cpp)
OBJS = $(patsubst src/%.cpp, obj/%.o, $(SRCS))

all : $(OBJS)
	$(CXX) $(OBJS) $(LDFLAGS) -o $(APP_NAME)

obj/%.o : src/%.cpp obj_dir
	$(CXX) -c $(CXXFLAGS) $< -o $@

obj_dir:
	mkdir obj -p

clean :
	-rm -f obj/*.o
	-rm -f $(APP_NAME)
