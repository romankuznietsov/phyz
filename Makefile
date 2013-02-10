APP_NAME = phyz

CXX = g++
CXXFLAGS = -pedantic -Wall -Wextra -std=c++11
LDFLAGS = -lGL -lGLU -lglut -lboost_thread -lboost_signals -lpthread -lyaml-cpp

SRCS = $(wildcard src/*.cpp) $(wildcard src/**/*.cpp)
OBJS = $(patsubst src/%.cpp, obj/%.o, $(SRCS))

all: $(APP_NAME)

$(APP_NAME) : objdir $(OBJS)
	$(CXX) $(OBJS) $(LDFLAGS) -o $(APP_NAME)

obj/%.o : src/%.cpp
	$(CXX) -c $(CXXFLAGS) $< -o $@

.PHONY: objdir
objdir:
	-mkdir -p obj/gxy

.PHONY: clean
clean :
	-rm -rf obj
	-rm -f $(APP_NAME)
