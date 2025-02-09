manki: main.o fsrs.o db.o utils.o skills/addition.o skills/multiplication.o skills/subtraction.o
	g++ main.cpp skills/addition.cpp skills/multiplication.cpp skills/subtraction.cpp db.cpp fsrs.cpp utils.cpp -l sqlite3 -o manki 

main.o: main.cpp
	g++ -c main.cpp

fsrs.o: fsrs.cpp fsrs.h
	g++ -c fsrs.cpp

db.o: db.cpp db.h
	g++ -c db.cpp
utils.o: utils.cpp utils.h
	g++ -c utils.cpp
skills/addition.o: skills/addition.cpp skills/addition.h
	g++ -c skills/addition.cpp
skills/multiplication.o: skills/multiplication.cpp skills/multiplication.h
	g++ -c skills/multiplication.cpp
skills/subtraction.o: skills/subtraction.cpp skills/subtraction.h
	g++ -c skills/subtraction.cpp



clean: 
	rm *.o manki
