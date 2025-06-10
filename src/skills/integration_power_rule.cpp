#include <iostream>
#include <random>

/**
 * Generates a string array that represents an integration power rule problem
 *
 * @return Returns a string representing a integration power rule problem, a string representing the solution, and an empty notes string 
 */
std::string* generate_integration_power_rule_problem() 
{
        int min = 1;
        int max = 10;

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distrib(min, max);

        int coefficient = distrib(gen);
        int exponent = distrib(gen);

        std::string problem = std::to_string(coefficient) + "x^{" + std::to_string(exponent) + "} = ?";
        std::string solution;
        if(coefficient % (exponent+1) == 0){
                solution = std::to_string(coefficient/(exponent+1)) + "x^{" + std::to_string(exponent+1) + "} + C ";
        } else{

                solution = "\\frac{" + std::to_string(coefficient) + "}{" + std::to_string(exponent+1) + "}x^{" + std::to_string(exponent+1) + "} + C";
        }
        std::string notes = "";

        std::string* problem_array = new std::string[3];
        problem_array[0] = problem;
        problem_array[1] = solution;
        problem_array[2] = notes; 

        return problem_array;
}
