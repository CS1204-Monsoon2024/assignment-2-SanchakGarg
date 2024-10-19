CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11
TARGET = main.out
SRC = HashTable.cpp

default: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)
