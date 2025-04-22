manki: backend.o fsrs.o db.o utils.o skills/addition.o skills/multiplication.o skills/subtraction.o latexpp/main.o 
	g++ -std=c++20 App.cpp MainFrame.cpp backend.cpp -fno-rtti skills/addition.cpp skills/multiplication.cpp skills/subtraction.cpp skills/power_rule.cpp skills/fraction_addition.cpp skills/two_by_two_det.cpp skills/three_by_three_det.cpp skills/quadratic_formula.cpp skills/sin_values.cpp skills/cos_values.cpp skills/tan_values.cpp skills/product_rule.cpp skills/two_by_two_matrix_multiplication.cpp skills/matrix_vector_multiplication.cpp skills/triangle_area.cpp skills/circle_area.cpp skills/integration_power_rule.cpp db.cpp fsrs.cpp utils.cpp latexpp/latex.cpp lib/linux_x64_libv8_monolith.a lib/libssl.a lib/libcrypto.a -Llib/ -lboost_system -lboost_atomic -lboost_filesystem -lssl -lcrypto -lwkhtmltox -l sqlite3 -lm -o manki -I include -I lib/boost_1_87_0 -DV8_COMPRESS_POINTERS  -I/usr/lib/wx/include/gtk3-unicode-3.2 -I/usr/include/wx-3.2 -DWXUSINGDLL -D__WXGTK3__ -D__WXGTK__ -D_FILE_OFFSET_BITS=64 -lwx_gtk3u_xrc-3.2 -lwx_gtk3u_html-3.2 -lwx_gtk3u_qa-3.2 -lwx_gtk3u_core-3.2 -lwx_baseu_xml-3.2 -lwx_baseu_net-3.2 -lwx_baseu-3.2



backend.o: backend.cpp
	g++ -std=c++20 -c backend.cpp -I include

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
skills/power_rule.o: skills/power_rule.cpp skills/power_rule.h
	g++ -c skills/subtraction.cpp
latexpp/latex.o: latexpp/latex.cpp latexpp/latex.hpp
	g++ -c latexpp/latex.cpp -I include
latexpp/main.o: latexpp/main.cpp
	g++ -c latexpp/main.cpp -I include -I lib/boost_1_87_0



debug: backend.o fsrs.o db.o utils.o skills/addition.o skills/multiplication.o skills/subtraction.o latexpp/main.o 
	g++ -g -std=c++20 App.cpp MainFrame.cpp backend.cpp -fno-rtti skills/addition.cpp skills/multiplication.cpp skills/subtraction.cpp skills/power_rule.cpp db.cpp fsrs.cpp utils.cpp latexpp/latex.cpp lib/linux_x64_libv8_monolith.a lib/libssl.a lib/libcrypto.a -Llib/ -lboost_system -lboost_atomic -lboost_filesystem -lssl -lcrypto -lwkhtmltox -l sqlite3 -lm -o manki -I include -I lib/boost_1_87_0 -DV8_COMPRESS_POINTERS  -I/usr/lib/wx/include/gtk3-unicode-3.2 -I/usr/include/wx-3.2 -DWXUSINGDLL -D__WXGTK3__ -D__WXGTK__ -D_FILE_OFFSET_BITS=64 -lwx_gtk3u_xrc-3.2 -lwx_gtk3u_html-3.2 -lwx_gtk3u_qa-3.2 -lwx_gtk3u_core-3.2 -lwx_baseu_xml-3.2 -lwx_baseu_net-3.2 -lwx_baseu-3.2



clean: 
	rm *.o manki
