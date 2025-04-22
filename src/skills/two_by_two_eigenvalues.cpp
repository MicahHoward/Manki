#include <iostream>
#include <random>

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
        std::string* returnValue = new std::string[2];
        returnValue[0] = problem;
        returnValue[1] = solution;

        return returnValue;
}
