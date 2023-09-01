./main : main.cpp sobolowen.cpp sobolowen.h
	g++ -O3 -mtune=native -std=c++17 -Wno-narrowing  main.cpp sobolowen.cpp -o ./main
	./main stateful > stateful_samples.txt
	./main stateless > stateless_samples.txt
	
.PHONY : clean
clean :
	rm ./main stateful_samples.txt stateless_samples.txt

