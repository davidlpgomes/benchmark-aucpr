CXX = g++
CXXFLAGS = -pedantic-errors -Wall -Wextra -Werror -O3
TARGET = bench

$(TARGET): main.o BatchPRAUC.o RollingPRAUC.o
	$(CXX) $(CXXFLAGS) -o $(TARGET) main.o BatchPRAUC.o RollingPRAUC.o

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp

BatchPRAUC.o: BatchPRAUC.hpp BatchPRAUC.cpp
	$(CXX) $(CXXFLAGS) -c BatchPRAUC.cpp

RollingPRAUC.o: RollingPRAUC.hpp RollingPRAUC.cpp
	$(CXX) $(CXXFLAGS) -c RollingPRAUC.cpp

clean:
	rm -f $(TARGET) *.o
