#include <iostream>
#include <random>

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
        std::string* returnValue = new std::string[3];
        returnValue[0] = problem;
        returnValue[1] = solution;
        returnValue[2] = "";

        return returnValue;
}
