# Makefile
CXX       = g++
CXXFLAGS  = -std=c++11 -Wall -O2
DEPS      = catalog.h
SRCS      = main.cpp catalog.cpp
OBJS      = $(SRCS:.cpp=.o)
TARGET    = program

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp $(DEPS)
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -f $(OBJS) $(TARGET) output.txt

.PHONY: all clean

