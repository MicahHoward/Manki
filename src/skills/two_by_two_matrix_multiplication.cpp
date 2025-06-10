#include <iostream>
#include <random>

/**
 * Generates a string array that represents a 2x2 matrix multiplication problem 
 *
 * @return Returns a string representing a 2x2 matrix multiplication problem, a string representing the solution, and an empty notes string 
 */
std::string* generate_two_by_two_matrix_multiplication_problem() 
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
 
        int determinant = (first_number * fourth_number) - (second_number * third_number);

        std::string problem = "\\begin{bmatrix}" + std::to_string(first_number) + " & " + std::to_string(second_number) + "\\\\" + 
                std::to_string(third_number) + " & " + std::to_string(fourth_number) + "\\end{bmatrix}" + "\\times" + "\\begin{bmatrix}" 
                + std::to_string(fifth_number) + " & " + std::to_string(sixth_number) + "\\\\" + std::to_string(seventh_number) + " & " + std::to_string(eighth_number) + "\\end{bmatrix}";
        std::string solution = "[[" + std::to_string(first_number*fifth_number + second_number*seventh_number) 
                + ", " + std::to_string(first_number*sixth_number + second_number*eighth_number) + "], [" + 
                std::to_string(third_number*fifth_number + fourth_number*seventh_number) + ", " + std::to_string(third_number*sixth_number + fourth_number*eighth_number) + "]]";
        std::string notes = "";

        std::string* problem_array = new std::string[3];
        problem_array[0] = problem;
        problem_array[1] = solution;
        problem_array[2] = notes; 

        return problem_array;
}
