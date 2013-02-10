APP_NAME = phyz

CXX = g++
CXXFLAGS = -pedantic -Wall -Wextra -std=c++11
LDFLAGS = -lGL -lGLU -lglut -lboost_thread -lpthread -lyaml-cpp

SRCS = $(wildcard src/*.cpp)
OBJS = $(patsubst src/%.cpp, obj/%.o, $(SRCS))

all: $(APP_NAME)

$(APP_NAME) : $(OBJS)
	$(CXX) $(OBJS) $(LDFLAGS) -o $(APP_NAME)

obj/%.o : src/%.cpp
	$(CXX) -c $(CXXFLAGS) $< -o $@

.PHONY: clean
clean :
	-rm -f obj/*.o
	-rm -f $(APP_NAME)
