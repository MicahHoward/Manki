#include <iostream>
#include <random>

std::string* generate_matrix_vector_multiplication_problem() 
{
        int min = 1;
        int max = 10;

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distrib(min, max);

        int first_number = distrib(gen);
        int second_number = distrib(gen);
        int third_number = distrib(gen);
        int fourth_number = distrib(gen);
        int fifth_number = distrib(gen);
        int sixth_number = distrib(gen);
        int seventh_number = distrib(gen);
        int eighth_number = distrib(gen);
        int ninth_number = distrib(gen);
 
        int determinant = (first_number * fourth_number) - (second_number * third_number);

        std::string problem = "\\begin{bmatrix}" + std::to_string(first_number) + " & " + std::to_string(second_number) + " &" + std::to_string(third_number)
                + "\\\\" + std::to_string(fourth_number) + " & " + std::to_string(fifth_number) + " & " + std::to_string(sixth_number) + "\\end{bmatrix}" +  
                "\\begin{bmatrix}" + std::to_string(seventh_number) + " & " + std::to_string(eighth_number) + " & " + std::to_string(ninth_number) + "\\end{bmatrix}";
        std::string solution = "[" + std::to_string(first_number*seventh_number + second_number*eighth_number + third_number*ninth_number) 
                + "," + std::to_string(fourth_number*seventh_number + fifth_number*eighth_number + sixth_number*ninth_number) + "]";
        std::string* returnValue = new std::string[3];
        returnValue[0] = problem;
        returnValue[1] = solution;
        returnValue[2] = "";

        return returnValue;
}
