APP_NAME = phyz

CXX = g++
CXXFLAGS = -pedantic -Wall -Wextra
LDFLAGS = -lGL -lGLU -lglut

SRCS = $(wildcard src/*.cpp)
OBJS = $(patsubst src/%.cpp, obj/%.o, $(SRCS))

TEST_SRCS = $(wildcard test/*.cpp)
TEST_OBJS = $(patsubst test/%.cpp, obj/%.o, $(TEST_SRCS))

all: $(APP_NAME)

$(APP_NAME) : $(OBJS)
	$(CXX) $(OBJS) $(LDFLAGS) -o $(APP_NAME)

test : OBJS_WITHOUT_MAIN = $(patsubst obj/main.o, , $(OBJS))
test : $(OBJS_WITHOUT_MAIN) $(TEST_OBJS)
	$(CXX) $(OBJS_WITHOUT_MAIN) $(TEST_OBJS) $(LDFLAGS) -o $(APP_NAME)_test

obj/%.o : src/%.cpp
	$(CXX) -c $(CXXFLAGS) $< -o $@

obj/%_test.o : test/%_test.cpp
	$(CXX) -c $(CXXFLAGS) $< -o $@


.PHONY: clean
clean :
	-rm -f obj/*.o
	-rm -f $(APP_NAME)
	-rm -f $(APP_NAME)_test
