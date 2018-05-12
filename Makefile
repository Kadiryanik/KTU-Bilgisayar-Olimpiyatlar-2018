all:
	gcc -o Soru-2.out Soru-2.c
	g++ -o Soru-3.out Soru-3.cpp
	gcc -o Soru-4.out Soru-4.c -lm
clean:
	rm -f *.out
	rm -f *output.txt
