#include <iostream>
#include <random>

/**
 * Generates a string array that represents a 3x3 matrix determinant problem 
 *
 * @return Returns a string representing a 3x3 matrix determinant problem, a string representing the solution, and an empty notes string 
 */
std::string* generate_three_by_three_det_problem() 
{
        int min = 1;
        int max = 10;

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distrib(min, max);
        
        int matrix[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
        for(int i = 0; i < 9; i ++){
                matrix[i] = distrib(gen);
        }
        int determinant = (matrix[0] * ((matrix[4] * matrix[8]) - (matrix[5] * matrix[7]))) - (matrix[1] * ((matrix[3] * matrix[8]) - (matrix[5] * matrix[6]))) + (matrix[2] * ((matrix[3] * matrix[7]) - (matrix[4] * matrix[6])));

        std::string problem = "\\begin{bmatrix}" + std::to_string(matrix[0]) + " & " + std::to_string(matrix[1]) + " & " + std::to_string(matrix[2])
                + "\\\\" + std::to_string(matrix[3]) + " & " + std::to_string(matrix[4]) + " & " + std::to_string(matrix[5])
                + "\\\\" + std::to_string(matrix[6]) + " & " + std::to_string(matrix[7]) + " & " + std::to_string(matrix[8]) + "\\end{bmatrix}";
        std::string solution = std::to_string(determinant);
        std::string notes = "";

        std::string* problem_array = new std::string[3];
        problem_array[0] = problem;
        problem_array[1] = solution;
        problem_array[2] = notes;

        return problem_array;
}
