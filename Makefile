APP_NAME = phyz

CXX = g++
CXXFLAGS = -pedantic -Wall -Wextra
LDFLAGS = -lGL -lGLU -lglut
TEST_CXXFLAGS = -Isrc -Iinclude
TEST_LDFLAGS = -Llib -lgtest -lgtest_main -lpthread

SRCS = $(wildcard src/*.cpp)
OBJS = $(patsubst src/%.cpp, obj/%.o, $(SRCS))

TEST_SRCS = $(wildcard test/*.cpp)
TEST_OBJS = $(patsubst test/%.cpp, obj/%.o, $(TEST_SRCS))

all: $(APP_NAME)

$(APP_NAME) : $(OBJS)
	$(CXX) $(OBJS) $(LDFLAGS) -o $(APP_NAME)

test : $(OBJS) $(TEST_OBJS)
	$(CXX) $(patsubst obj/main.o, , $(OBJS)) $(TEST_OBJS) $(LDFLAGS) $(TEST_LDFLAGS) -o $(APP_NAME)_test

obj/%.o : src/%.cpp
	$(CXX) -c $(CXXFLAGS) $< -o $@

obj/%_test.o : test/%_test.cpp
	$(CXX) -c $(CXXFLAGS) $(TEST_CXXFLAGS) $< -o $@


.PHONY: clean
clean :
	-rm -f obj/*.o
	-rm -f $(APP_NAME)
	-rm -f $(APP_NAME)_test
