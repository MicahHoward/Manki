#include <iostream>
#include <random>

/**
 * Generates a string array that represents a 2x2 matrix eigenvalues problem 
 *
 * @return Returns a string representing a 2x2 matrix eigenvalues problem, a string representing the solution, and an empty notes string 
 */
std::string* generate_two_by_two_eigenvalues_problem() 
{
        int min = -10;
        int max = 10;

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distrib(min, max);

        int first_number = distrib(gen);
        int second_number = distrib(gen);
        int third_number = distrib(gen);
        int fourth_number = distrib(gen);
        int determinant = (first_number * fourth_number) - (second_number * third_number);

        std::complex<double> xone = (std::complex<double>(-b, 0) + std::sqrt(std::complex<double>(pow(b, 2) - (4*a*c), 0)))/std::complex<double>((2*a),0); 
        std::complex<double> xtwo = (std::complex<double>(-b, 0) - std::sqrt(std::complex<double>(pow(b, 2) - (4*a*c), 0)))/std::complex<double>((2*a),0); 



        std::string problem = "\\begin{bmatrix}" + std::to_string(first_number) + " & " + std::to_string(second_number) + "\\\\" + std::to_string(third_number) + " & " + std::to_string(fourth_number) + "\\end{bmatrix}";
        std::string solution = std::to_string(determinant);
        std::string notes = "";

        std::string* problem_array = new std::string[3];
        problem_array[0] = problem;
        problem_array[1] = solution;
        problem_array[2] = notes; 

        return problem_array;
}
