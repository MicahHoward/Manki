manki: main.o fsrs.o db.o utils.o skills/addition.o skills/multiplication.o skills/subtraction.o latexpp/main.o 
	g++ -std=c++20 main.cpp -fno-rtti skills/addition.cpp skills/multiplication.cpp skills/subtraction.cpp db.cpp fsrs.cpp utils.cpp latexpp/latex.cpp lib/linux_x64_libv8_monolith.a lib/libssl.a lib/libcrypto.a -Llib/ -lboost_system -lboost_atomic -lboost_filesystem -lssl -lcrypto -lwkhtmltox -l sqlite3 -lm -o manki -I include -I lib/boost_1_87_0 -DV8_COMPRESS_POINTERS


main.o: main.cpp
	g++ -std=c++20 -c main.cpp -I include

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
latexpp/latex.o: latexpp/latex.cpp latexpp/latex.hpp
	g++ -c latexpp/latex.cpp -I include
latexpp/main.o: latexpp/main.cpp
	g++ -c latexpp/main.cpp -I include -I lib/boost_1_87_0





clean: 
	rm *.o manki
