CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11
TARGET = main.out
SRC = main.cpp

default: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

run: $(TARGET)
	./$(TARGET)

# Clean up
clean:
	rm -f $(TARGET)
