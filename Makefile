APP_NAME = phyz

CXX = g++
CXXFLAGS = -pedantic -Wall -Wextra -std=c++11 -O3
LDFLAGS = -lGL -lGLU -lglut -lboost_thread -lboost_signals -lboost_program_options -lpthread -lyaml-cpp

SRCS = $(wildcard src/*.cpp) $(wildcard src/**/*.cpp)
OBJS = $(patsubst src/%.cpp, obj/%.o, $(SRCS))

all: $(APP_NAME)

$(APP_NAME) : objdir $(OBJS)
	$(CXX) $(OBJS) $(LDFLAGS) -o $(APP_NAME)

obj/%.o : src/%.cpp
	$(CXX) -c $(CXXFLAGS) $< -o $@

.PHONY: objdir
objdir:
	-mkdir -p obj/burden

.PHONY: clean
clean :
	-rm -rf obj
	-rm -f $(APP_NAME)
