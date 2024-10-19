default: main.cpp
	g++ -Wall main.cpp -o main.out

run: main.out 
	./main.out 


clean:
	rm *.out
